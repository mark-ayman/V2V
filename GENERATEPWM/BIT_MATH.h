#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(NUM,BIT_NUM)  NUM = NUM | (1<<BIT_NUM)

#define CLR_BIT(NUM,BIT_NUM)  NUM = NUM & ~(1<<BIT_NUM)

#define TOG_BIT(NUM,BIT_NUM)  NUM = NUM ^ (1<<BIT_NUM)

#define GET_BIT(NUM,BIT_NUM)  (NUM>>BIT_NUM) & 1 
 
#endif