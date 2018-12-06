#include "mongoose.h"
#include<time.h>
#include<stdio.h>

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  if (ev == MG_EV_HTTP_REQUEST) {
    mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
  }
}
void functioncall(){
    printf("function has been called");
    

}

int main(void) {
  clock_t start_t;
  struct mg_mgr mgr;
  struct mg_connection *nc;

  mg_mgr_init(&mgr, NULL);
  printf("Starting web server on port %s\n", s_http_port);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    printf("Failed to create listener\n");
    return 1;
  }

  // Set up HTTP server parameters
  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = ".";  // Serve current directory
  s_http_server_opts.enable_directory_listing = "yes";
  start_t=clock();
  printf("start time:%ld\n",start_t);
  printf("clocks per sec = %ld\n", CLOCKS_PER_SEC);
  //start_t=(double)start_t/(double)CLOCKS_PER_SEC;
  printf("start time/clocks_per_sec: %ld\n",start_t);
  for (;;){
      printf("if statement: %lf\n",((double)clock()-start_t)/CLOCKS_PER_SEC);
   //   if((((double)clock())/CLOCKS_PER_SEC)-start_t <= 60){
//	 functioncall(); 
   //   }
     // start_t=(double)clock();
     // start_t=start_t/CLOCKS_PER_SEC;
      mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);
  return 0;
}
