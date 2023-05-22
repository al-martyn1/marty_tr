@for %%i in (*.h*) do @(
    rem echo Sorting includes in %%i
    umba-sort-headers --overwrite=Y --user --group=1 --block=1 %%i
)