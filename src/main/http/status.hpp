#ifndef POSEIDON_HTTP_STATUS_HPP_
#define POSEIDON_HTTP_STATUS_HPP_

namespace Poseidon {

enum HttpStatus {
	HTTP_CONTINUE			 	= 100,
	HTTP_SWITCH_PROTOCOLS		= 101,
	HTTP_OK 					= 200,
	HTTP_CREATED 				= 201,
	HTTP_ACCEPTED 				= 202,
	HTTP_PARTIAL 				= 203,
	HTTP_NO_CONTENT 			= 204,
	HTTP_RESET_CONTENT 			= 205,
	HTTP_PARTIAL_CONTENT 		= 206,
	HTTP_WEBDAV_MULTI_STATUS 	= 207,
	HTTP_AMBIGUOUS 				= 300,
	HTTP_MOVED 					= 301,
	HTTP_REDIRECT 				= 302,
	HTTP_REDIRECT_METHOD 		= 303,
	HTTP_NOT_MODIFIED 			= 304,
	HTTP_USE_PROXY 				= 305,
	HTTP_REDIRECT_KEEP_VERB 	= 307,
	HTTP_BAD_REQUEST 			= 400,
	HTTP_DENIED 				= 401,
	HTTP_PAYMENT_REQ 			= 402,
	HTTP_FORBIDDEN 				= 403,
	HTTP_NOT_FOUND 				= 404,
	HTTP_BAD_METHOD 			= 405,
	HTTP_NONE_ACCEPTABLE 		= 406,
	HTTP_PROXY_AUTH_REQ 		= 407,
	HTTP_REQUEST_TIMEOUT 		= 408,
	HTTP_CONFLICT 				= 409,
	HTTP_GONE 					= 410,
	HTTP_LENGTH_REQUIRED 		= 411,
	HTTP_PRECOND_FAILED 		= 412,
	HTTP_REQUEST_TOO_LARGE 		= 413,
	HTTP_URI_TOO_LONG 			= 414,
	HTTP_UNSUPPORTED_MEDIA 		= 415,
	HTTP_RETRY_WITH 			= 449,
	HTTP_SERVER_ERROR 			= 500,
	HTTP_NOT_SUPPORTED 			= 501,
	HTTP_BAD_GATEWAY 			= 502,
	HTTP_SERVICE_UNAVAIL 		= 503,
	HTTP_GATEWAY_TIMEOUT 		= 504,
	HTTP_VERSION_NOT_SUP 		= 505
};

struct HttpStatusDesc {
	const char *descShort;
	const char *descLong;
};

HttpStatusDesc getHttpStatusCodeDesc(HttpStatus status);

}

#endif
