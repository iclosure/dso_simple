
function y = sinc_interp(x,SampleN,InterpN)
%%  Sinc Interpolation Examples
%%  Matlab code for sinc interpolation
%m = 0:SampleN-1;
factor = (SampleN-1)/InterpN;
for i=0:InterpN-1
    tsum = 0.0;
    for m=0:SampleN-1
        t = pi*(m-i*factor);
        %t = (m-i*factor)*2048;
        if(t == 0)
            tsum = tsum + x(m+1);
        else
            %tsum = tsum + TRIG_sin(t) * x(m+1) / t;
            tsum = tsum + sin(t) * x(m+1) / t;
        end
    end
    y(i+1) = tsum;
end
