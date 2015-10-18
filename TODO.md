linux error handling with errno
clean up Linux/Socket.cpp and Windows/Socket.cpp

make a test which hosts both tcp and udp (separate tests) and then connects to the loopback and exchanges dat

Add actual unit tests (not just integration tests)
Add documentation

Add async sockets
Add overlapped i/o
Add io competion ports
Add registered io

Add a task queue where async results are posted
	or maybe not, since iocp might do callbacks on worker threads...
	think about this one...
	maybe implement iocp first and then see what fits

Add a parameter to each function for LoggingInterface that lets the user supply a logging library
	What about destructors, which can't take a param?
	No. Gonna have to store it upon construction.