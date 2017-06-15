#ifndef CCP_NL_H
#define CCP_NL_H

#include <net/sock.h>

// CCP connection lookup
struct ccp_connection {
    uint16_t index;
    struct sock *sk;
};

int ccp_init_connection_map(void);
void ccp_free_connection_map(void);
uint16_t ccp_connection_start(struct sock *sk);
void ccp_connection_free(uint16_t sid);
struct sock *ccp_connection_lookup(uint16_t sid);

void nl_recv_cwnd(struct sk_buff *skb);
int nl_send_conn_create(
    struct sock *nl_sk, 
    uint16_t ccp_index, 
    uint32_t startSeq
);
void nl_send_ack_notif(
    struct sock *nl_sk, 
    uint16_t ccp_index, 
    u32 cumAck, 
    u32 srtt
);

enum drop_type {
    DROP_TIMEOUT,
    DROP_DUPACK,
    DROP_ECN
};

int nl_send_drop_notif(
    struct sock *nl_sl,
    uint16_t ccp_index,
    enum drop_type dtype
);

#endif
