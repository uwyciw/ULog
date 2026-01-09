function size = TypeSize(type_name)
%% 
%获得各类型的字节大小。
switch(type_name)
    case {'bool'}
        size = 1;
    case {'char'}
        size = 1;
    case {'int8_t'}
        size = 1;
    case {'uint8_t'}
        size = 1;
    case {'int16_t'}
        size = 2;
    case {'uint16_t'}
        size = 2;
    case {'int32_t'}
        size = 4;
    case {'uint32_t'}
        size = 4;
    case {'int64_t'}
        size = 8;
    case {'uint64_t'}
        size = 8;
    case {'float'}
        size = 4;
    case {'double'}
        size = 8;
end

end