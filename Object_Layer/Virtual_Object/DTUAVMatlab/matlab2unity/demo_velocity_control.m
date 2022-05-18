target_position_x = 1;
target_position_y = 1;
target_position_z = 1;
socketChannel = StartSocket(8080);
time = 10;
a = [socketChannel(1,1);socketChannel(1,2);1;0;1;0;2;3];
for i=0:0.01:10
    state = CurrentUavState(socketChannel);
    vx = (1-exp((target_position_x-state(1,1))*-0.8))*2.0/(1+exp((target_position_x-state(1,1))*-0.8));
    vy = (1-exp((target_position_y-state(2,1))*-0.8))*2.0/(1+exp((target_position_y-state(2,1))*-0.8));
    vz = (1-exp((target_position_z-state(3,1))*-0.8))*2.0/(1+exp((target_position_z-state(3,1))*-0.8));
    a = [socketChannel(1,1);socketChannel(1,2);vx;vy;vz;0;0;0];
    TargetUavVelocity(a);
    pause(0.2);
end
CloseSocket(socketChannel)