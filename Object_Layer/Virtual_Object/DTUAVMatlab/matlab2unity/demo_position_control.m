target_position_x = 1;
target_position_y = 1;
target_position_z = 1;
socketChannel = StartSocket(8080);
time = 10;
a = [socketChannel(1,1);socketChannel(1,2);1;1;1;0;0;0;1];
for i=0:0.01:10
    state = CurrentUavState(socketChannel);
    a = [socketChannel(1,1);socketChannel(1,2);target_position_x;target_position_y;target_position_z;0;0;i/10;1];
    TargetUavLocalPosition(a);
    pause(0.2);
end
CloseSocket(socketChannel)