define one = 
hadoop com.sun.tools.javac.Main PageCount.java
endef
define two =
jar cf pc.jar PageCount*.class
endef
define three = 
hadoop jar pc.jar PageCount /user/cs440/haleyg/input.dat /user/cs440/haleyg/output
endef
define four =  
hdfs dfs -rm -r /user/cs440/haleyg/output  
endef
define five = 
hdfs dfs -cat /user/cs440/haleyg/output/part-r-00000
endef
makef: ; $(one)
makej: ; $(two)
run: ; $(three)
check: ; $(five)
clean: ; $(four)

.ONESHELL:
