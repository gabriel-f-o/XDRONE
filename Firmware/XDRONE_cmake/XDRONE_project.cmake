#eyJidWlsZFByZXNldHMiOnsiZGVmYXVsdF9jb25maWciOnsibmFtZSI6ImRlZmF1bHRfY29uZmlnIiwiZGVmaW5pdGlvbnMiOltdLCJyZW1vdmVkRmxhZ3MiOnsiQyI6WyItZyJdLCJDWFgiOltdLCJBU00iOltdfSwiYWRkaXRpb25hbEZsYWdzIjp7IkMiOlsiLWczIl0sIkNYWCI6W10sIkFTTSI6W119fX0sImRpcmVjdG9yaWVzIjpbXX0=
get_target_property(interface_compile_options slc_XDRONE INTERFACE_COMPILE_OPTIONS)
	list(REMOVE_ITEM interface_compile_options $<$<AND:$<CONFIG:default_config>,$<COMPILE_LANGUAGE:C>>:-g>)
set_target_properties(XDRONE PROPERTIES INTERFACE_COMPILE_OPTIONS "${interface_compile_options}")

target_compile_options(XDRONE PRIVATE
	$<$<AND:$<CONFIG:default_config>,$<COMPILE_LANGUAGE:C>>:-g3>
)
