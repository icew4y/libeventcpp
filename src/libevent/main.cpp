// libevent.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <event2/event.h>
#include <event2/listener.h>

using namespace std;

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	event_base* context = event_base_new();


	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8080);
	evconnlistener* listener = evconnlistener_new_bind(context,
		[](struct evconnlistener* e, evutil_socket_t s, struct sockaddr* sin, int socklen, void* argc) {
		cout << "call back  to listener.";
	},
		nullptr,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
		10,
		(sockaddr*)& sin,
		sizeof(sin));

	event_base_dispatch(context);


	evconnlistener_free(listener);
	event_base_free(context);

// 	event_config* config = event_config_new();
// 
// 
// 	const char** methods = event_get_supported_methods();
// 	for (int i = 0; methods[i] != nullptr; i++)
// 	{
// 		cout << "method:" << i << ", " << methods[i];
// 	}
// 
// 	event_base* base = event_base_new_with_config(config);
// 
// 	event_config_free(config);
// 	event_base_free(base);
}
