/*
 *	
 * Copyright (c) 2016 Cisco Systems, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 * 
 *   Neither the name of the Cisco Systems, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#include "nfv9.h"


struct nfv9_field_type nfv9_fields[] = {                                 
  { "RESERVED",                      0,   0  },                       
  { "IN_BYTES",                      1,   0  },     
  { "IN_PKTS",                       2,   0  },    
  { "FLOWS",                         3,   0  },    
  { "PROTOCOL",                      4,   1  },    
  { "TOS",                           5,   1  },    
  { "TCP_FLAGS",                     6,   1  },   
  { "L4_SRC_PORT",                   7,   2  },   
  { "IPV4_SRC_ADDR",                 8,   4  },   
  { "SRC_MASK",                      9,   1  },   
  { "INPUT_SNMP",                   10,   0  },   
  { "L4_DST_PORT",                  11,   2  },   
  { "IPV4_DST_ADDR",                12,   4  },   
  { "DST_MASK",                     13,   1  },   
  { "OUTPUT_SNMP",                  14,   0  },   
  { "IPV4_NEXT_HOP",                15,   4  },   
  { "SRC_AS",                       16,   0  },   
  { "DST_AS",                       17,   0  },   
  { "BGP_IPV4_NEXT_HOP",            18,   4  },   
  { "MUL_DST_PKTS",                 19,   0  },   
  { "MUL_DST_BYTES",                20,   0  },   
  { "LAST_SWITCHED",                21,   4  },   
  { "FIRST_SWITCHED",               22,   4  },   
  { "OUT_BYTES",                    23,   0  },   
  { "OUT_PKTS",                     24,   0  },   
  { "IPV6_SRC_ADDR",                27,   16 },   
  { "IPV6_DST_ADDR",                28,   16 },   
  { "IPV6_SRC_MASK",                29,   1  },   
  { "IPV6_DST_MASK",                30,   1  },   
  { "IPV6_FLOW_LABEL",              31,   3  },   
  { "ICMP_TYPE",                    32,   2  },   
  { "MUL_IGMP_TYPE",                33,   1  },   
  { "SAMPLING_INTERVAL",            34,   4  },   
  { "SAMPLING_ALGORITHM",           35,   1  },   
  { "FLOW_ACTIVE_TIMEOUT",          36,   2  },   
  { "FLOW_INACTIVE_TIMEOUT",        37,   2  },   
  { "ENGINE_TYPE",                  38,   1  },   
  { "ENGINE_ID",                    39,   1  },   
  { "TOTAL_BYTES_EXP",              40,   0  },   
  { "TOTAL_PKTS_EXP",               41,   0  },   
  { "TOTAL_FLOWS_EXP",              42,   0  }, 
  { "VENDOR_PROPRIETARY",           43,   0  },  /* length? */
  { "IPV4_SRC_PREFIX",              44,   4  },
  { "IPV4_DST_PREFIX",              45,   4  },
  { "MPLS_TOP_LABEL_TYPE",          46,   1  }, 
  { "MPLS_TOP_LABEL_IP_ADDR",       47,   4  },   
  { "FLOW_SAMPLER_ID",              48,   1  },   
  { "FLOW_SAMPLER_MODE",            49,   1  },   
  { "FLOW_SAMPLER_RANDOM_INTERVAL", 50,   4  },
  { "MIN_TTL",                      52,   1  },
  { "MAX_TTL",                      53,   1  },
  { "IPV4_IDENT",                   54,   2  },
  { "DST_TOS",                      55,   1  },   
  { "SRC_MAC",                      56,   6  },   
  { "DST_MAC",                      57,   6  },   
  { "SRC_VLAN",                     58,   2  },   
  { "DST_VLAN",                     59,   2  },   
  { "IP_PROTOCOL_VERSION",          60,   1  },   
  { "DIRECTION",                    61,   1  },   
  { "IPV6_NEXT_HOP",                62,  16  },   
  { "BGP_IPV6_NEXT_HOP",            63,  16  },   
  { "IPV6_OPTION_HEADERS",          64,   4  },
  { "VENDOR_PROPRIETARY",           65,   0  },
  { "VENDOR_PROPRIETARY",           66,   0  },
  { "VENDOR_PROPRIETARY",           67,   0  },
  { "VENDOR_PROPRIETARY",           68,   0  },
  { "VENDOR_PROPRIETARY",           69,   0  },
  { "MPLS_LABEL_1",                 70,   3  },   
  { "MPLS_LABEL_2",                 71,   3  },   
  { "MPLS_LABEL_3",                 72,   3  },   
  { "MPLS_LABEL_4",                 73,   3  },   
  { "MPLS_LABEL_5",                 74,   3  },   
  { "MPLS_LABEL_6",                 75,   3  },   
  { "MPLS_LABEL_7",                 76,   3  },   
  { "MPLS_LABEL_8",                 77,   3  },   
  { "MPLS_LABEL_9",                 78,   3  },   
  { "MPLS_LABEL_10",                79,   3  },   
  { "IN_DST_MAC",                   80,   6  },
  { "OUT_SRC_MAC",                  81,   6  },
  { "IF_NAME",                      82,   0  },
  { "IF_DESC",                      83,   0  },
  { "SAMPLER_NAME",                 84,   0  },
  { "IN_PERMANENT_BYTES",           85,   0  },
  { "IN_PERMANENT_PKTS",            86,   0  }, 
  { "VENDOR_PROPRIETARY",           87,   0  },
  { "FRAGMENT_OFFSET",              88,   2  },
  { "FORWARDING_STATUS",            89,   1  },
  { "MPLS_PAL_RD",                  90,   8  },
  { "MPLS_PREFIX_LEN",              91,   1  },
  { "SRC_TRAFFIC_INDEX",            92,   4  },
  { "DST_TRAFFIC_INDEX",            93,   4  },
  { "APPLICATION_DESCRIPTION",      94,   0  },
  { "APPLICATION_TAG",              95,   0  }, /* 1+n ? */
  { "APPLICATION_NAME",             96,   0  },
  { "VENDOR_PROPRIETARY",           97,   0  }, /* missing */
  { "postipDiffServCodePoint",      98,   1  },
  { "replication_factor",           99,   4  },
  { "DEPRECATED",                  100,   0  },
  { "RESERVED",                    101,   0  },
  { "layer2packetSectionOffset",   102,   0, },
  { "layer2packetSectionSize",     103,   0, },
  { "layer2packetSectionData",     104,   0, },
  { "SALT",                        105,   200, }, /* NONSTANDARD */
};

struct nfv9_field_type *get_nfv9_field_type(u_short typecode) {
  if (typecode > MAX_TYPES) {
    typecode = 0;
  }
  return &nfv9_fields[typecode];
}

struct template_handler *get_template_handler(unsigned int template_id);

void nfv9_hdr_init(struct nfv9_hdr *h) {
  h->VersionNumber = htons(9);
}


#define TEMPLATE 0

void nfv9_template_flowset_init(struct nfv9_template_flowset *fs) {
  fs->flowset_hdr.FlowSetID = TEMPLATE;
  fs->flowset_hdr.Length = 0;
}

void nfv9_template_flowset_add_field(struct nfv9_template_flowset *fs, 
				     struct nfv9_template_field f) {
  /* unsigned int index; */

  /* index = (fs->flowset_hdr.Length - sizeof(struct nfv9_flowset_hdr)); */
  /* index = index / (sizeof(struct nfv9_template_field)) + 1; */

  /* fs->fields[index] = f; */
}

#define NFV9_PORT 2055

void nfv9_template_key_init(struct nfv9_template_key *k, u_long addr, u_long id, u_short template_id) {
  k->src_addr.s_addr = addr;
  k->src_id = id;
  k->template_id = template_id;
} 


void nfv9_exporter_init(struct nfv9_exporter *e, const char *hostname) {
  struct hostent *host;
  /* set collector address */

  e->msg_count = 0;
  e->sysUpTime = time(NULL);
  
  e->socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (e->socket < 0) { 
    perror("cannot create socket"); 
  } 

  /* set local (exporter) address */
  memset((char *)&e->exprt_addr, 0, sizeof(e->exprt_addr)); 
  e->exprt_addr.sin_family = AF_INET; 
  e->exprt_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  e->exprt_addr.sin_port = htons(0); /* ANY */
  if (bind(e->socket, 
	   (struct sockaddr *)&e->exprt_addr, 
	   sizeof(e->exprt_addr)) < 0) { 
    perror("bind failed"); 
  }

  /* set remote (collector) address */
  memset((char*)&e->clctr_addr, 0, sizeof(e->clctr_addr)); 
  e->clctr_addr.sin_family = AF_INET; 
  e->clctr_addr.sin_port = htons(NFV9_PORT);
  host = gethostbyname(hostname); 
  if (!host) { 
    fprintf(stderr, "could not find address for collector %s\n", hostname);     
  }

  memcpy((void *)&e->clctr_addr.sin_addr, host->h_addr_list[0], host->h_length);
 
  return;
}


/*
 * SOURCE_ID is hardcoded now for simplicity
 */
#define SOURCE_ID 1

void nfv9_exporter_send_msg(struct nfv9_exporter *e, struct nfv9_msg *msg) {
  /* send a message to the server */ 
  ssize_t bytes;
  
 
  msg->hdr.Count = 0;  /* number of flowsets */

  msg->hdr.VersionNumber = htons(9);
  msg->hdr.sysUpTime = e->sysUpTime;
  msg->hdr.UNIXSecs = time(NULL);
  msg->hdr.SequenceNumber = htonl(e->msg_count);
  msg->hdr.SourceID = htonl(SOURCE_ID);  
 
  bytes = sendto(e->socket, msg, 0, 0, (struct sockaddr *)&e->clctr_addr, 
		 sizeof(e->clctr_addr));
  if (bytes < 0) { 
    perror("nfv9 message could not be sent"); 
  }
}

void nfv9_template_init(struct nfv9_template *t, u_short TemplateID) {
  t->hdr.TemplateID = TemplateID; 
  t->hdr.FieldCount = 0; 
}

void nfv9_template_add_field(struct nfv9_template *t, struct nfv9_template_field f) {
  t->fields[t->hdr.FieldCount] = f;
  t->hdr.FieldCount++; 
}

#define nfv9_template_field(a) ((struct nfv9_template_field) {a, 0})
#define nfv9_template_field_len(a,b) ((struct nfv9_template_field) {a, b})


void encode_unsigned(const void *uint, unsigned int len, void *output) {
  switch(len) {
  case 1:
    ((u_char *)output)[0] = ((u_char *)uint)[0];
    break;
  case 2:
    ((u_short *)output)[0] = htons(((u_short *)uint)[0]);
    break;
  case 4:
    ((u_int *)output)[0] = htonl(((u_int *)uint)[0]);    
    break;
  default:
    fprintf(stderr, "error - integer too large in encoding\n");
  }
}

void decode_unsigned(const void *uint, unsigned int len, void *output) {
  switch(len) {
  case 1:
    ((u_char *)output)[0] = ((u_char *)uint)[0];
    break;
  case 2:
    ((u_short *)output)[0] = ntohs(((u_short *)uint)[0]);
    break;
  case 4:
    ((u_int *)output)[0] = ntohl(((u_int *)uint)[0]);    
    break;
  default:
    fprintf(stderr, "error - integer too large in decoding\n");
  }
}

void print_unsigned(const void *uint, unsigned int len) {
  switch(len) {
  case 1:
    printf("%u\n", ((u_char *)uint)[0]); 
    break;
  case 2:
    printf("%u\n", ((u_short *)uint)[0]); 
    break;
  case 4:
    printf("%u\n", ((u_int *)uint)[0]); 
    break;
  default:
    fprintf(stderr, "error - bad integer size in print_unsigned \n");
  }
}


int nfv9_flow_record_encode(const void *record, 
			    const struct nfv9_template *template,
			    void *output, 
			    unsigned int output_len) {
  unsigned int total_length = 0, element_length, i, num_elements;
  
  num_elements = template->hdr.FieldCount;
  if (num_elements > NFV9_MAX_ELEMENTS) {
    fprintf(stderr, "error: too many elements in record\n");
  }

  /* encode each information element */
  for (i=0; i<num_elements; i++) {
    element_length = template->fields[i].FieldLength;
    total_length += element_length;
    if (total_length > output_len) {
      return -total_length; /* error */
    }
    encode_unsigned(record, element_length, output);
    record += element_length;
    output += element_length;
  }
  return total_length;
}

int nfv9_flow_record_decode(const void *input, 
			    const struct nfv9_template *template,
			    void *record,  /* output */ 
			    unsigned int output_len) {
  unsigned int total_length = 0, element_length, i, num_elements;
  
  num_elements = template->hdr.FieldCount;
  if (num_elements > NFV9_MAX_ELEMENTS) {
    fprintf(stderr, "error: too many elements in record\n");
  }

  /* decode each information element */
  for (i=0; i<num_elements; i++) {
    element_length = template->fields[i].FieldLength;
    total_length += element_length;
    if (total_length > output_len) {
      return -total_length; /* error */
    }
    decode_unsigned(input, element_length, record);
    input += element_length;
    record += element_length;
  }
  return total_length;
}

void nfv9_data_flowset_encode_init(struct nfv9_data_flowset *fs,
				   const struct nfv9_template *t) {
  fs->flowset_hdr.FlowSetID = htons(t->hdr.TemplateID);
  fs->flowset_hdr.Length = 4; /* length so far is just header */
}

void nfv9_data_flowset_encode_record(struct nfv9_data_flowset *fs,
				     const void *record,
				     const struct nfv9_template *template) {
  void *writehere = fs->flowset + (fs->flowset_hdr.Length - 4);
  unsigned int len = NFV9_MAX_LEN - fs->flowset_hdr.Length;
  int bytes_encoded;

  bytes_encoded = nfv9_flow_record_encode(record, template, writehere, len);
  if ( bytes_encoded < 0) {
    fprintf(stderr, "encoding error\n");
  };

  fs->flowset_hdr.Length += bytes_encoded;
}

void nfv9_data_flowset_encode_final(struct nfv9_data_flowset *fs) {

  /* add padding if needed */

  /* convert header to network byte order */
  fs->flowset_hdr.Length = htons(fs->flowset_hdr.Length);

}

void nfv9_flow_record_print(const void *record,
			    const struct nfv9_template *template) {  
  unsigned int element_length, i, num_elements;
  
  num_elements = template->hdr.FieldCount;
  if (num_elements > NFV9_MAX_ELEMENTS) {
    fprintf(stderr, "error: too many elements in record\n");
  }

  /* print each information element */
  for (i=0; i<num_elements; i++) {
    element_length = template->fields[i].FieldLength;
    printf("%s: ", 
	   get_nfv9_field_type(template->fields[i].FieldType)->FieldName);
    print_unsigned(record, element_length);
    record += element_length;
  }
}


void nfv9_data_flowset_decode_and_handle(struct nfv9_data_flowset *fs) {
  unsigned int template_id;
  int len_remaining, ret;
  struct template_handler *h;
  void *readhere = fs->flowset;
  u_char buffer[NFV9_MAX_LEN];

  /* decode header */
  template_id = ntohs(fs->flowset_hdr.FlowSetID);
  len_remaining = ntohs(fs->flowset_hdr.Length) - 4;

  /* get appropriate handler for template */
  h = get_template_handler(template_id);
  if (h == NULL) {
    printf("no handler found for this template (%u)\n", template_id);
    return; /* can't do anything with this flowset */
  }

  /* loop over all records in flowset */
  while (len_remaining > 0) {
    printf("\nprocessing flow record:\n");
    ret = nfv9_flow_record_decode(readhere, &h->template, buffer, NFV9_MAX_LEN);
    printf("got %d bytes\n", ret);
    if (ret < 1) {
      break;
    }
    nfv9_flow_record_print(buffer, &h->template);
    readhere += ret;
    len_remaining -= ret;
    printf("remaining length: %d\n", len_remaining);
  }  
}


void nfv9_template_print(const struct nfv9_template *template) {  
  unsigned int field_length, field_type, num_elements, i;

  printf("TemplateID: %u\n", template->hdr.TemplateID);
  printf("FieldCount: %u\n", template->hdr.FieldCount);
  
  num_elements = template->hdr.FieldCount;
  if (num_elements > NFV9_MAX_ELEMENTS) {
    fprintf(stderr, "error: too many elements in template\n");
  }

  /* print each field */
  for (i=0; i<num_elements; i++) {
    field_length = template->fields[i].FieldLength;
    field_type = template->fields[i].FieldType;
    printf("%s: \tlength: %u\n", 
	   get_nfv9_field_type(field_type)->FieldName, 
	   field_length);
  }
}

void nfv9_template_flowset_encode_init(struct nfv9_template_flowset *fs) {
  fs->flowset_hdr.FlowSetID = TEMPLATE;
  fs->flowset_hdr.Length = 4; /* length so far is just header */
}

void nfv9_template_flowset_encode_template(struct nfv9_template_flowset *fs,
				      const struct nfv9_template *template) {
  void *writehere = fs->flowset + (fs->flowset_hdr.Length - 4);
  unsigned int len = NFV9_MAX_LEN - fs->flowset_hdr.Length;
  unsigned int i, num_elements, total_length = 0;

  num_elements = template->hdr.FieldCount;
  if (num_elements > NFV9_MAX_ELEMENTS) {
    fprintf(stderr, "error: too many elements in template flowset\n");
  }

  /* encode template header */
  encode_unsigned(&template->hdr.TemplateID, 2, writehere);
  writehere += 2;
  encode_unsigned(&template->hdr.FieldCount, 2, writehere);
  writehere += 2;
   
  /* encode each field in template */
  for (i=0; i<num_elements; i++) {
    total_length += 2;
    if (total_length > len) {
      fprintf(stderr, "error: not enough room in template flowset\n");
    }
    encode_unsigned(&template->fields[i].FieldType, 2, writehere);
    writehere += 2;
    encode_unsigned(&template->fields[i].FieldLength, 2, writehere);
    writehere += 2;
  } 

  fs->flowset_hdr.Length += total_length;
}

void nfv9_template_flowset_encode_final(struct nfv9_template_flowset *fs) {

  /* add padding if needed */

  /* convert header to network byte order */
  fs->flowset_hdr.Length = htons(fs->flowset_hdr.Length);

}


void nfv9_template_flowset_decode_init(struct nfv9_template_flowset *fs) {
  //  fs->flowset_hdr.Length; 
}

void nfv9_template_decode(const void *input,
			  struct nfv9_template *template,
			  unsigned int template_len) {
  unsigned int num_elements, total_length, i;
  const struct nfv9_template *input_template = input;

  template->hdr.TemplateID = ntohs(input_template->hdr.TemplateID);
  num_elements = ntohs(input_template->hdr.FieldCount);
  if (num_elements > NFV9_MAX_ELEMENTS) {
    fprintf(stderr, "error: too many elements in template flowset\n");
  }
  template->hdr.FieldCount = num_elements;
  total_length = 4;

  /* decode each field in template */
  for (i=0; i<num_elements; i++) {
    total_length += 4;
    if (total_length > template_len) {
      fprintf(stderr, "error: not enough room in template decode\n");
    }
    template->fields[i].FieldType = 
      ntohs(input_template->fields[i].FieldType);
    template->fields[i].FieldLength = 
      ntohs(input_template->fields[i].FieldLength);
  } 

}



struct nfv9_salt_flow_record {
  u_char salt;  /* placeholder */
};

void template() {
  struct nfv9_template t;

  /*
     NFv9 template for conventional 5-tuple

   { "OUT_BYTES",                    23,   0  },   
   { "OUT_PKTS",                     24,   0  },   
   { "IPV4_SRC_ADDR",                 8,   4  }
   { "IPV4_DST_ADDR",                12,   4  },   
   { "L4_SRC_PORT",                   7,   2  },   
   { "L4_DST_PORT",                  11,   2  },   
   { "PROTOCOL",                      4,   1  },    
 
   */
  
  nfv9_template_init(&t, 1);
  nfv9_template_add_field(&t, nfv9_template_field(23));
  nfv9_template_add_field(&t, nfv9_template_field(24));
  nfv9_template_add_field(&t, nfv9_template_field(8));
  nfv9_template_add_field(&t, nfv9_template_field(12));
  nfv9_template_add_field(&t, nfv9_template_field(7));
  nfv9_template_add_field(&t, nfv9_template_field(11));
  nfv9_template_add_field(&t, nfv9_template_field(4));

}

struct template_handler *template_handler_list = NULL;
unsigned int template_id_max = 256;

unsigned int 
nfv9_register_template_handler(const struct nfv9_template *template, 
				    template_handler_func f) {
  struct template_handler *h = malloc(sizeof(struct template_handler));

  if (h == NULL) {
    printf("error: could not allocate handler\n");
    return 0;
  }
  h->template_id = template_id_max++;   /* note: should check for wrap */
  h->func = f;
  memcpy(&h->template, template, sizeof(struct nfv9_template));
  h->next = template_handler_list;
  template_handler_list = h;
  
  return h->template_id;
}

void nfv9_unregister_template_handler(unsigned int template_id) {
  ; /* remove list entry */
}

struct template_handler *get_template_handler(unsigned int template_id) {
  struct template_handler *h;

  /* find handler */
  h = template_handler_list;
  while (h != NULL) {
    if ((h->template_id == template_id) || (h->template_id == 0)) {
      return h;
    }
    h = h->next;
  }
  fprintf(stderr, "error: could not find handler\n");
  return NULL;
}

#if 0
void handle_data(unsigned int template_id,
		 void *data,
		 unsigned int len) {
  struct template_handler *h;


  /* find handler */
  h = template_handler_list;
  while (h != NULL) {
    if ((h->template_id == template_id) || (h->template_id == 0)) {
      return h->func(data, len);
    }
    h = h->next;
  }
  fprintf(stderr, "error: could not find handler\n");
}
#endif /* 0 */

void nfv9_exporter_init_msg(struct nfv9_exporter *e,
			    struct nfv9_msg *msg) {

  msg->hdr.VersionNumber = htons(9);
  msg->hdr.sysUpTime = e->sysUpTime;
  msg->hdr.UNIXSecs = time(NULL);
  msg->hdr.SequenceNumber = htonl(e->msg_count);
  msg->hdr.SourceID = htonl(SOURCE_ID);  
  
  msg->hdr.Count = 0;  /* number of flowsets */
  
}

void nfv9_process_times(struct flow_record *nf_record, const void *time_data, struct timeval *old_val_time, int max_length_array, int pkt_time_index) {
  short tmp_packet_time;
  int repeated_times;
  int j;
  for (j = 0; j < max_length_array; j += 2) {
    tmp_packet_time = htons(*(const short *)(time_data + j));

    short tmp_packet_length = htons(*(const short *)(time_data + j - max_length_array));

    // look for run length encoding
    if (tmp_packet_length < 0 && tmp_packet_length != -32768) {
      int repeated_length = tmp_packet_length * -1 - 1;
      while (repeated_length > 0) {
	if (pkt_time_index < MAX_NUM_PKT_LEN) {
	  nf_record->pkt_time[pkt_time_index] = *old_val_time;
	  pkt_time_index++;
	} else {
	  break;
	}
	repeated_length -= 1;
      }
    }

    // value represents the arrival time of the packet
    if (tmp_packet_time >= 0) {
      old_val_time->tv_sec += (time_t)(tmp_packet_time/1000);
      old_val_time->tv_usec += (unsigned long int)(tmp_packet_time - ((int)(tmp_packet_time/1000.0))*1000)*1000;

      // make sure to check for wrap around, weirdness happens when usec >= 1000000
      if (old_val_time->tv_usec >= 1000000) {
	old_val_time->tv_sec += (time_t)((int)(old_val_time->tv_usec / 1000000));
	old_val_time->tv_usec %= 1000000;
      }
      
      if (pkt_time_index < MAX_NUM_PKT_LEN) {
	nf_record->pkt_time[pkt_time_index] = *old_val_time;
	pkt_time_index++;
      } else {
	break;
      }
    }
    // value represents the number of packets that were observed that had an arrival time
    //   equal to the last observed arrival time
    else {
      repeated_times = tmp_packet_time * -1;
      int k;
      for (k = 0; k < repeated_times; k++) {
	if (pkt_time_index < MAX_NUM_PKT_LEN) {
	  nf_record->pkt_time[pkt_time_index] = *old_val_time;
	  pkt_time_index++;
	} else {
	  break;
	}
      }
    }
  }
}

void nfv9_process_lengths(struct flow_record *nf_record, const void *length_data, int max_length_array, int pkt_len_index) {
  int old_val = 0;
  short tmp_packet_length;
  int repeated_length;
  int j;
  for (j = 0; j < max_length_array; j += 2) {
    tmp_packet_length = htons(*(const short *)(length_data + j));
    // value represents the length of the packet
    if (tmp_packet_length >= 0) {
      if (tmp_packet_length > 0) {
	nf_record->op += 1;
      }
      old_val = tmp_packet_length;
      if (pkt_len_index < MAX_NUM_PKT_LEN) {
	nf_record->pkt_len[pkt_len_index] = tmp_packet_length;
	nf_record->ob += tmp_packet_length;
	pkt_len_index++;
      } else {
	break;
      }
    }
    // value represents the number of packets that were observed that had a length
    //   equal to the last observed packet length
    else {
      // padding value, "8000", flow is done
      if (tmp_packet_length == -32768) {
	break;
      }
      repeated_length = tmp_packet_length * -1;
      nf_record->op += repeated_length;
      int k;
      for (k = 0; k < repeated_length; k++) {
	if (pkt_len_index < MAX_NUM_PKT_LEN) {
	  nf_record->pkt_len[pkt_len_index] = old_val;
	  nf_record->ob += old_val;
	  pkt_len_index++;
	} else {
	  break;
	}
      }
    }
  }
}

void nfv9_flow_key_init(struct flow_key *key, const struct nfv9_template *cur_template, const void *flow_data) {
  int i;
  for (i = 0; i < cur_template->hdr.FieldCount; i++) {
    switch (htons(cur_template->fields[i].FieldType)) {
    case IPV4_SRC_ADDR:
      key->sa.s_addr = *(const int *)flow_data;
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case IPV4_DST_ADDR:
      key->da.s_addr = *(const int *)flow_data;
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case L4_SRC_PORT:
      key->sp = htons(*(const short *)flow_data);
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case L4_DST_PORT:
      key->dp = htons(*(const short *)flow_data);
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case PROTOCOL:
      key->prot = *(const char *)flow_data;
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    default:
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    }
  }
}


void nfv9_process_flow_record(struct flow_record *nf_record, const struct nfv9_template *cur_template, const void *flow_data, int record_num) {
  struct timeval old_val_time;
  unsigned int total_ms;
  int i,j;
  for (i = 0; i < cur_template->hdr.FieldCount; i++) {
    switch (htons(cur_template->fields[i].FieldType)) {
    case IN_PKTS:
      if (record_num == 0) {
	if (htons(cur_template->fields[i].FieldLength) == 4) {
	  nf_record->np += htonl(*(const int *)(flow_data));
	} else {
	  nf_record->np += __builtin_bswap64(*(const uint64_t *)(flow_data));
	}
      }
      
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
      
    case FIRST_SWITCHED:
      if (nf_record->start.tv_sec + nf_record->start.tv_usec == 0) {
	nf_record->start.tv_sec = (time_t)((int)(htonl(*(const unsigned int *)flow_data) / 1000));
	nf_record->start.tv_usec = (time_t)((int)htonl(*(const unsigned int *)flow_data) % 1000)*1000;
      }

      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case LAST_SWITCHED:
      if (nf_record->end.tv_sec + nf_record->end.tv_usec == 0) {
	nf_record->end.tv_sec = (time_t)((int)(htonl(*(const int *)flow_data) / 1000));
	nf_record->end.tv_usec = (time_t)((int)htonl(*(const int *)flow_data) % 1000)*1000;
      }

      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_SRLT:
      total_ms = 0;
      for (j = 0; j < 20; j++) {
	if (htons(*(const short *)(flow_data+j*2)) == 0) {
	  break;
	}

	nf_record->tls_info.tls_len[j] = htons(*(const unsigned short *)(flow_data+j*2));
	nf_record->tls_info.tls_time[j].tv_sec = (total_ms+htons(*(const unsigned short *)(flow_data+40+j*2))+nf_record->start.tv_sec*1000+nf_record->start.tv_usec/1000)/1000;
	nf_record->tls_info.tls_time[j].tv_usec = ((total_ms+htons(*(const unsigned short *)(flow_data+40+j*2))+nf_record->start.tv_sec*1000+nf_record->start.tv_usec/1000)%1000)*1000;
	total_ms += htons(*(const unsigned short *)(flow_data+40+j*2));

	nf_record->tls_info.tls_type[j].content = *(const unsigned char *)(flow_data+80+j);
	nf_record->tls_info.tls_type[j].handshake = *(const unsigned char *)(flow_data+100+j);
	nf_record->tls_info.tls_op += 1;
      }
      
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_CS:
      for (j = 0; j < 125; j++) {
	if (htons(*(const short *)(flow_data+j*2)) == 65535) {
	  break;
	}
	nf_record->tls_info.ciphersuites[j] = htons(*(const unsigned short *)(flow_data+j*2));
	nf_record->tls_info.num_ciphersuites += 1;
      }
      
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_EXT:
      for (j = 0; j < 35; j++) {
	if (htons(*(const short *)(flow_data+j*2)) == 0) {
	  break;
	}
	nf_record->tls_info.tls_extensions[j].length = htons(*(const unsigned short *)(flow_data+j*2));
	nf_record->tls_info.tls_extensions[j].type = htons(*(const unsigned short *)(flow_data+70+j*2));
	nf_record->tls_info.tls_extensions[j].data = NULL;
	nf_record->tls_info.num_tls_extensions += 1;
      }
      
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_VERSION:
      nf_record->tls_info.tls_v = *(const char *)flow_data;
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_CLIENT_KEY_LENGTH:
      nf_record->tls_info.tls_client_key_length = htons(*(const short *)flow_data);
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_SESSION_ID:
      nf_record->tls_info.tls_sid_len = htons(*(const short *)flow_data);
      nf_record->tls_info.tls_sid_len = min(nf_record->tls_info.tls_sid_len,256);
      memcpy(nf_record->tls_info.tls_sid, flow_data+2, nf_record->tls_info.tls_sid_len);
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case TLS_HELLO_RANDOM:
      memcpy(nf_record->tls_info.tls_random, flow_data, 32);
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case IDP:
      nf_record->idp_len = htons(cur_template->fields[i].FieldLength);
      nf_record->idp = malloc(nf_record->idp_len);
      memcpy(nf_record->idp, flow_data, nf_record->idp_len);
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case SPLT:
    case SPLT_NGA: ;
      int max_length_array = (int)htons(cur_template->fields[i].FieldLength)/2;
      const void *length_data = flow_data;
      const void *time_data = flow_data + max_length_array;
      
      int pkt_len_index = nf_record->op;
      int pkt_time_index = nf_record->op;

      // process the lengths array in the SPLT data
      nfv9_process_lengths(nf_record, length_data, max_length_array, pkt_len_index);

      // initialize the time <- this is where we should use the nfv9 timestamp
      
      if (pkt_time_index > 0) {
	old_val_time.tv_sec = nf_record->pkt_time[pkt_time_index-1].tv_sec;
	old_val_time.tv_usec = nf_record->pkt_time[pkt_time_index-1].tv_usec;
      } else {
	old_val_time.tv_sec = nf_record->start.tv_sec;
	old_val_time.tv_usec = nf_record->start.tv_usec;
      }
      

      // process the times array in the SPLT data
      nfv9_process_times(nf_record, time_data, &old_val_time, max_length_array, pkt_time_index);

      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    case BYTE_DISTRIBUTION: ;
      int field_length = htons(cur_template->fields[i].FieldLength);
      int bytes_per_val = field_length/256;
      for (j = 0; j < 256; j++) { 
	// 1 byte vals
	if (bytes_per_val == 1) {
	  nf_record->byte_count[j] = (int)*(const char *)(flow_data+j*bytes_per_val);
	}
	// 2 byte vals
	else if (bytes_per_val == 2) {
	  nf_record->byte_count[j] = htons(*(const short *)(flow_data+j*bytes_per_val));  
	}
	// 4 byte vals
	else {
	  nf_record->byte_count[j] = htonl(*(const int *)(flow_data+j*bytes_per_val));
	}
      }

      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    default:
      flow_data += htons(cur_template->fields[i].FieldLength);
      break;
    }
  }
}
