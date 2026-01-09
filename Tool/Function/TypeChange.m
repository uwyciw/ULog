function matlab_type = TypeChange(ulog_type)

switch(ulog_type)
    case {'bool'}
        matlab_type = {'uint8'};
    case {'char'}
        matlab_type = 1;
    case {'int8_t'}
        matlab_type = {'int8'};
    case {'uint8_t'}
        matlab_type = {'uint8'};
    case {'int16_t'}
        matlab_type = {'int16'};
    case {'uint16_t'}
        matlab_type = {'uint16'};
    case {'int32_t'}
        matlab_type = 4;
    case {'uint32_t'}
        matlab_type = {'uint32'};
    case {'int64_t'}
        matlab_type = {'int64'};
    case {'uint64_t'}
        matlab_type = {'uint64'};
    case {'float'}
        matlab_type = {'single'};
    case {'double'}
        matlab_type = {'double'};
end

end