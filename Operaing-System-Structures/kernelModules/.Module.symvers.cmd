cmd_/home/loyio/OSConceptProgrammingProjects/Operaing-System-Structures/kernelModules/Module.symvers := sed 's/ko$$/o/' /home/loyio/OSConceptProgrammingProjects/Operaing-System-Structures/kernelModules/modules.order | scripts/mod/modpost -m -a   -o /home/loyio/OSConceptProgrammingProjects/Operaing-System-Structures/kernelModules/Module.symvers -e -i Module.symvers   -T -