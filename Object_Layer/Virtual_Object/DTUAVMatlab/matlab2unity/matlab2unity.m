socketChannel = StartSocket(8080);
%recv  
%state = CurrentUavState(socketChannel);

%send
%a = [socketChannel(1,1);socketChannel(1,2);1;0;1;0;2;3];
%state = TargetUavVelocity(a);
%CloseSocket(socketChannel)