set AppPath="%1"
set ProcessCount=2
start cmd /k "mpiexec -n %ProcessCount% %AppPath%"