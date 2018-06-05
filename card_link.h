#ifndef CARD_LINK_H
#define CARD_LINK_H
extern "C" char *read_block(int block_num);
extern "C" int *write_block(int block_num);
extern "C" char *read_frame(int frame);
extern "C" int write_frame(int frame, char *data);
extern "C" int get_perm();
#endif  // CARD_LINK_H