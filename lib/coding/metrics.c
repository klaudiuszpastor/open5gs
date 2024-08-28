#include "metrics.h"
#include "core/ogs-core.h"

#define INITIAL_DECODE_TIME 0.0
#define DEFAULT_AVERAGE_TIME 0.0

static metrics_t metrics;

void init_metrics(void) {
    metrics.decode_calls_success = 0;
    metrics.decode_calls_failure = 0;
    metrics.total_decode_time = INITIAL_DECODE_TIME;
    ogs_info("Metrics initialized: decode_calls_success=%lu, decode_calls_failure=%lu, total_decode_time=%f",
            metrics.decode_calls_success, metrics.decode_calls_failure, metrics.total_decode_time);
}

void increment_decode_success(void) {
    metrics.decode_calls_success++;
    ogs_info("Incremented decode success count: decode_calls_success=%lu", metrics.decode_calls_success);
}

void increment_decode_failure(void) {
    metrics.decode_calls_failure++;
    ogs_info("Incremented decode failure count: decode_calls_failure=%lu", metrics.decode_calls_failure);
}

void record_decode_time(double elapsed_time) {
    metrics.total_decode_time += elapsed_time;
    ogs_info("Recorded decode time: elapsed_time=%f, total_decode_time=%f", elapsed_time, metrics.total_decode_time);
}

double get_average_decode_time(void) {
    double average_time = DEFAULT_AVERAGE_TIME;
    if (metrics.decode_calls_success != 0) {
        average_time = metrics.total_decode_time / metrics.decode_calls_success;
    }
    ogs_info("Calculated average decode time: average_time=%.3f", average_time);
    return average_time;
}

void print_metrics(void) {
    ogs_info("Printing metrics:");
    ogs_info("Decode Success Calls: %lu\n", metrics.decode_calls_success);
    ogs_info("Decode Failure Calls: %lu\n", metrics.decode_calls_failure);
    ogs_info("Total Decode Time: %f seconds\n", metrics.total_decode_time);
    ogs_info("Average Decode Time: %.3f seconds\n", get_average_decode_time());
}
