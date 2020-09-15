#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <log/log.h>
#include <data_structure/queue.h>
#include "code.h"
#include "request_manager.h"

struct Request {
        void *server_data;
        int client_id;
        unsigned char *buf;
        size_t buf_size;
};

struct RequestQueue {
        struct Queue *queue;
};

static struct RequestQueue *requests = NULL;
static pthread_mutex_t thread_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t thread_condition = PTHREAD_COND_INITIALIZER;

void request_manager_init
(void)
{
        requests = code_malloc(sizeof(*requests));
        requests->queue = queue_new(&code_malloc, &code_mfree);
}

void request_manager_enqueue
(void *server_data, int client_id, unsigned char *buf, size_t buf_size)
{
        assert(requests);
        assert(requests->queue);
        assert(buf);
        assert(buf_size > 0);

        struct Request *request = NULL;

        request = code_malloc(sizeof(*request));
        request->server_data = server_data;
        request->client_id = client_id;
        request->buf = code_malloc(buf_size);
        request->buf_size = buf_size;

        memcpy(request->buf, buf, buf_size);

        pthread_mutex_lock(&thread_mutex);
        queue_enqueue(requests->queue, request);
        pthread_cond_signal(&thread_condition);
        pthread_mutex_unlock(&thread_mutex);
}

static struct Request *request_manager_dequeue
(void)
{
        assert(requests);
        assert(requests->queue);
        return queue_dequeue(requests->queue);
}

void *request_manager_start_handling_requests
(void *p)
{
        assert(requests);

        struct Request *request = NULL;

        log_info("Starting to handle requests");

        while (1) {
                pthread_mutex_lock(&thread_mutex);

                request = request_manager_dequeue();

                if (!request) {
                        pthread_cond_wait(&thread_condition, &thread_mutex);
                        request = request_manager_dequeue();
                }

                pthread_mutex_unlock(&thread_mutex);

                code_request_handle(
                        request->server_data,
                        request->client_id,
                        request->buf,
                        request->buf_size
                );

                code_mfree(request->buf);
                code_mfree(request);
        }

        return NULL;
}
