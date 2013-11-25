size=size(gyroY);
size=size-1;
zeit=transpose(0:0.004:size*0.004);




gyroY=[zeit, gyroY];
gyroR=[zeit, gyroR];
gyroP=[zeit, gyroP];
cfroll=[zeit, cfroll];
cfpitch=[zeit, cfpitch];
accR=[zeit, accR];
accP=[zeit, accP];


clear size
clear zeit