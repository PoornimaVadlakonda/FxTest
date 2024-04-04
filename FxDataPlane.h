#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <poll.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h> 
#include <resolv.h>

#ifndef FxDATAPLANE_H
#define FxDATAPLANE_H

#define FxTEDP__MT__STOP_DATA_TRAFFIC_REQUEST					1
#define FxTEDP__MT__STOP_DATA_TRAFFIC_RESPONSE					2
#define FxTEDP__MT__STOP_ALL_DATA_TRAFFIC_REQUEST				3
#define FxTEDP__MT__STOP_ALL_DATA_TRAFFIC_RESPONSE				4
#define FxTEDP__MT__START_DATA_TRAFFIC_REQUEST					5
#define FxTEDP__MT__START_DATA_TRAFFIC_RESPONSE					6

#define FxTEDP__ACTION_SEND_GI_PACKET							1
#define FxTEDP__ACTION_SEND_GTP_PACKET							2
#define FxTEDP__ACTION_SEND_GI_PROTOCOL_PACKET					3
#define FxTEDP__ACTION_SEND_GTP_PROTOCOL_PACKET					4
#define FxTEDP__ACTION_SEND_GTP_LOAD							5
#define FxTEDP__ACTION_SEND_GTP_ICMP_PACKET						6
#define FxTEDP__ACTION_STOP_PACKETS								7
#define FxTEDP__ACTION_STOP_ALL_PACKETS							8

typedef struct __fxdataplane_message_header
{
	uint32_t MessageType;
	uint32_t MessageLength;
	uint32_t MessageNo;
	uint8_t * siSocket;

} FxDataPlaneMessageHeader;

typedef struct __fxdataplane_request
{
	FxDataPlaneMessageHeader Header;
	uint64_t UEId;
	uint32_t PDUSessionId;
	uint32_t UPFTeid;
	uint32_t RANTeid;
	uint32_t UPFIP;
	uint32_t RANIP;
	uint32_t UEIP;
	uint32_t Action;
	uint32_t NoOfPacketsToSend;
	uint32_t Duration;
	uint32_t PacketsPerSecond;
	uint32_t PCapFileIndex;
	uint8_t	 IMSI[28];
} FxDataPlaneRequest;

typedef struct __fxdataplane_response
{
	FxDataPlaneMessageHeader Header;
	uint32_t ResponseStatus;
	uint64_t UEId;
	uint32_t TotalPacketsSent;
	uint32_t TotalPacketsReceived;
	uint64_t TotalBufferSent;
	uint64_t TotalBufferReceived;
} FxDataPlaneResponse;

void FxTEDP__UpdatePacketInfo( uint8_t * sPtr, uint32_t flowId, uint32_t pktlen);

void FxTEDP__GetPacketInfo( uint8_t ** sPtr, uint32_t * upfTeid, uint32_t * ranTeid, 
	uint32_t * upfip, uint32_t * flowId, uint32_t * gtpSeqNo, uint32_t * tcpSeqNo, 
	uint32_t * srcip, uint32_t * dstip, uint16_t * srcport, uint16_t * dstport, uint8_t * protocol);

void FxTEDP__UpdatePacketInfo2( uint8_t * sPtr, uint32_t flowId, uint32_t pktlen, uint32_t coreId);

void FxTEDP__GetPacketInfo2( uint8_t ** sPtr, uint32_t * upfTeid, uint32_t * ranTeid, 
	uint32_t * upfip, uint32_t * flowId, uint32_t * gtpSeqNo, uint32_t * tcpSeqNo, 
	uint32_t * srcip, uint32_t * dstip, uint16_t * srcport, uint16_t * dstport, uint8_t * protocol, uint32_t coreId);


void FxTEDP__Init( char * ip, int port, int coreCount);

	
#endif

