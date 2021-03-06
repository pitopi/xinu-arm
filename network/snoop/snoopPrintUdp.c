/**
 * @file snoopPrintUdp.c
 * @provides snoopPrintUdp
 * 
 * $Id: snoopPrintUdp.c 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <network.h>
#include <snoop.h>
#include <stdio.h>
#include <udp.h>

static void snoopPrintUdpPort(ushort port, char *descrp)
{
    switch (net2hs(port))
    {
    case UDP_PORT_RDATE:
        sprintf(descrp, "(Time)");
        break;
    case UDP_PORT_DHCPS:
        sprintf(descrp, "(BOOTP/DHCP Server)");
        break;
    case UDP_PORT_DHCPC:
        sprintf(descrp, "(BOOTP/DHCP Client)");
        break;
    case UDP_PORT_TRACEROUTE:
        sprintf(descrp, "(Traceroute)");
        break;
    default:
        sprintf(descrp, "");
        break;
    }
}

/**
 * Print contents of an UDP packet
 * @param pkt the packet
 * @return OK if print successful, SYSERR if error occurs
 */
int snoopPrintUdp(struct udpPkt *udp, char verbose)
{
    char descrp[40];
    char output[40];

    /* Error check pointer */
    if (NULL == udp)
    {
        return SYSERR;
    }

    if (verbose >= SNOOP_VERBOSE_ONE)
    {
        printf(" ----- UDP Header -----\n");
        /* Source port */
        if (verbose >= SNOOP_VERBOSE_TWO)
        {
            snoopPrintUdpPort(net2hs(udp->srcPort), descrp);
        }
        else
        {
            sprintf(descrp, "");
        }
        sprintf(output, "%d %s", net2hs(udp->srcPort), descrp);
        printf("  Src Port: %-25s ", output);

        /* Destination port */
        if (verbose >= SNOOP_VERBOSE_TWO)
        {
            snoopPrintUdpPort(net2hs(udp->dstPort), descrp);
        }
        else
        {
            sprintf(descrp, "");
        }
        sprintf(output, "%d %s", net2hs(udp->dstPort), descrp);
        printf("Dst Port: %-25s\n", output);

        if (verbose >= SNOOP_VERBOSE_TWO)
        {
            /* Message length */
            sprintf(output, "%d bytes", net2hs(udp->len));
            printf("  Message length: %-19s ", output);
            /* Checksum */
            printf("Checksum: 0x%04X\n", net2hs(udp->chksum));
            /*pseudohdr[0] = src;
               pseudohdr[1] = dst;
               pseudohdr[2] = net2hs(udp->len);
               pseudohdr[2] += (IP_PROTOCOL_UDP << 16); */
        }
    }

    return OK;
}
