#ifndef METRICS_H
#define METRICS_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t decode_calls_success;   
    uint64_t decode_calls_failure;   
    double total_decode_time;        
} metrics_t;

void init_metrics(void);
void increment_decode_success(void);
void increment_decode_failure(void);
void record_decode_time(double elapsed_time);
double get_average_decode_time(void);
void print_metrics(void);

#ifdef __cplusplus
}
#endif

#endif /* METRICS_H */
