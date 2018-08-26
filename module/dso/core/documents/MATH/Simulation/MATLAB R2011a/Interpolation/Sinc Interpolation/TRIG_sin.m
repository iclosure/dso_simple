%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       TRIG_sin
% angle :0 ~ 1024 %
function result = TRIG_sin(angle)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       trigonometric functions
%   NOTE:
%   All trigonometric functions are for internal usage only and
%   use the following conventions:
%      Angles: 4096 <==> 360?
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       sin / cos (internal)
%  Angle : 90/1024?
%  Data  : 1/1024
trigsin = [
	0,   ...%  %  0/16 *90?%
	100, ...%  %  1/16 *90?%
	200, ...%  %  2/16 *90?%
	297, ...%  %  3/16 *90?%
	392, ...%  %  4/16 *90?%
	483, ...%  %  5/16 *90?%
	569, ...%  %  6/16 *90?%
	650, ...%  %  7/16 *90?%
	724, ...%  %  8/16 *90?%
	792, ...%  %  9/16 *90?%
	851, ...%  % 10/16 *90?%
	903, ...%  % 11/16 *90?%
	946, ...%  % 12/16 *90?%
	980, ...%  % 13/16 *90?%
	1004,...%  % 14/16 *90?%
	1019,...%  % 15/16 *90?%
	1024    %  % 16/16 *90?%
];
%define
TRIG_90DEG    = 1024;
TRIG_45DEG    = (TRIG_90DEG)  / 2;
TRIG_180DEG   = (TRIG_90DEG)  * 2;
TRIG_360DEG   = (TRIG_90DEG)  * 4;
TRIG_360DEG_1 = (TRIG_360DEG) - 1;

	IsNeg =0;
	angle = rem(angle,TRIG_360DEG);  % reduce to 0-360 degrees %
	if angle > TRIG_180DEG
		angle = angle - TRIG_180DEG;
        IsNeg = 1;
    end
	if angle > TRIG_90DEG  % between 90-180 %
		angle = TRIG_180DEG - angle;   % use sine symetry %
    end
	% Now angle is reduced to 0?<= <= 90?%
	i = fix(angle / 64) + 1;
    factor = 64-(rem(angle,64));
    t = trigsin(i)*factor;
    if (factor-64) == 0
		t = t + trigsin(i+1)*(64-factor);
    end
	t = (t+32) / 64;   % divide,incl. rounding %
    if IsNeg ~= 1
        result = t;
    else
        retult = 0-t;
    end
    result = t;
end