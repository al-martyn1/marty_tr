@rem --enum-definition - -F=enumName
@rem --enum-name  -E=NAME

@rem set GEN_FLAGS=--enum-flags=enum-class,type-decl,serialize,deserialize,lowercase

@set LANGTAGFORMAT_DEF=-E=LangTagFormat -F=@LangTagFormat.txt

@set FLAFS_DEF=--enum-flags=enum-class,type-decl
@set FLAFS_SERIALIZE=--enum-flags=enum-class,serialize,deserialize,lowercase


umba-enum-gen @enums.rsp  %FLAFS_DEF%        %LANGTAGFORMAT_DEF% ..\enums_decl.h
umba-enum-gen @enums.rsp  %FLAFS_SERIALIZE%  %LANGTAGFORMAT_DEF% ..\enums_serialization.h


