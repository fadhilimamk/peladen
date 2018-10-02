#include <sys/types.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <stdlib.h>
#include <evhttp.h>
#include <stdio.h>
#include <event.h>
#include <string>
#include <err.h>

using namespace std;
const int PORT = 8080;

void generic_handler(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf;
    int fd = -1;
    int sz = 0;
    FILE * fp;

    buf = evbuffer_new();
    if (buf == NULL)
        err(1, "failed to create response buffer");
    
    string s_req(evhttp_request_uri(req));
    printf("   - Handling requests [%s]\n", s_req.c_str());

    if (s_req.compare("/500b.html") == 0) {
        fp = fopen ("data/500b.html", "r");
        fd = fileno(fp);
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
    } else if (s_req.compare("/20kb.html")==0){
        fp = fopen ("data/20kb.html", "r");
        fd = fileno(fp);
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
    } else {
        fp = fopen ("data/index.html", "r");
        fd = fileno(fp);
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
    }
    
    evbuffer_add_file(buf, fd, 0, sz);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
    fclose(fp);
}

int main(int argc, char **argv) {
    
    struct evhttp *httpd;
    event_init();
    httpd = evhttp_start("0.0.0.0", PORT);

    printf("\n >> Server is listening on http://localhost:%d\n\n", PORT);

    /* Set a callback for all requests. */
    evhttp_set_gencb(httpd, generic_handler, NULL);

    /* Not reached in this code as it is now. */
    event_dispatch();
    evhttp_free(httpd);
    
    return 0;
}