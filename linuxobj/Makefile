####################################################
#
#  选择是否打印命令
Q := @

#
# 定义总控Makefile所在的文件路径
#
top_dir = $(PWD)/..
cur_dir = $(PWD)

###################################################
# 编译配置文件[Makefile]路径
COMPILERDIRS := ./compiler
####################################################
# 源文件和头文件暂存路径
SRCDIRS      := ./src
export SRCDIRS 
#####################################################
#####################################################
# 定义工程最终输出的文件的路径
EXECDIRS       := ./Output/bin
RESOURCE_EDIRS := ./Output
# 
# 最终产生的可执行文件名
EXECNAME       := dsolinx.bin
export EXECDIRS EXECNAME
#####################################################
#####################################################
# 定义工程资源文件子路径列表
RESOURCE_SDIRS := $(top_dir)/resource

#####################################################
#####################################################
# 定义工程文件子路径列表
#
##^##  公共源文件路径
SUBDIRS := $(top_dir)/com
SUBDIRS += $(top_dir)/com/datatable
##^##  main 主函数入口文件
SUBDIRS += $(top_dir)/main
##^##  dso 部分的文件所有源文件路径
SUBDIRS += $(top_dir)/module/dso/bsp
SUBDIRS += $(top_dir)/module/dso/config
SUBDIRS += $(top_dir)/module/dso/core
SUBDIRS += $(top_dir)/module/dso/file/bmp
SUBDIRS += $(top_dir)/module/dso/file/myxml
SUBDIRS += $(top_dir)/module/dso/menuFunc
SUBDIRS += $(top_dir)/module/dso/picture
SUBDIRS += $(top_dir)/module/dso/picture/binarymap
SUBDIRS += $(top_dir)/module/dso/picture/bitmap
SUBDIRS += $(top_dir)/module/dso/variables
SUBDIRS += $(top_dir)/module/dso/variables/menu
##^##  dsp 部分的文件所有源文件路径
SUBDIRS += $(top_dir)/module/dsp/com
#SUBDIRS += $(top_dir)/module/dsp/src/datagen
#SUBDIRS += $(top_dir)/module/dsp/src/dataproc/fourier
SUBDIRS += $(top_dir)/module/dsp/src/dso_dsp
#SUBDIRS += $(top_dir)/module/dsp/src/dso_dsp/picproc
#SUBDIRS += $(top_dir)/module/dsp/src/external
##^##  gui 部分的文件所有源文件路径
SUBDIRS += $(top_dir)/module/gui/antialias
SUBDIRS += $(top_dir)/module/gui/config
SUBDIRS += $(top_dir)/module/gui/core
SUBDIRS += $(top_dir)/module/gui/driver
SUBDIRS += $(top_dir)/module/gui/font
##^##  XXXX 部分的文件所有源文件路径[用户可添加]

#####################################################
#####################################################

# The command used to create file or file folder.
MKDIR  = mkdir -p
#######################################################################
# The command used to copy file.
#CP     = cp -u
CP     = cp -uf
# 参数：
# -a   ：相当于 -pdr 的意思；
# -d   ：若来源文件为连结文件的属性(link file)，则复制连结文件属性而非档案本身；
# -f   ：为强制 (force) 的意思，若有重复或其它疑问时，不会询问使用者，而强制复制；
# -i   ：若目的檔(destination)已经存在时，在覆盖时会先询问是否真的动作！
# -l   ：进行硬式连结 (hard link) 的连结档建立，而非复制档案本身；
# -p   ：连同档案的属性一起复制过去，而非使用预设属性；
# -r   ：递归持续复制，用于目录的复制行为；
# -s   ：复制成为符号连结文件 (symbolic link)，亦即『快捷方式』档案；
# -u   ：若 destination 比 source 旧才更新 destination ！
# 最后需要注意的，如果来源档有两个以上，则最后一个目的文件一定要是『目录』才行！
#######################################################################
# The command used to delete file.
RM     = -rm -rf

#
# 定义多目标
#
poly_exes := StartTip
poly_exes += CreateFile
poly_exes += CopyFile
poly_exes += Compile
poly_exes += PrintInfo
poly_exes += EndTip

.PHONY : all NODEP_yes objs tags ctags clean distclean help show
all : $(poly_exes)

StartTip :
	@echo
	@echo ///////////////////// Start Make /////////////////////
	@echo 
CreateFile:
	@echo '1>' Create target files ...
	$(Q)$(MKDIR) $(EXECDIRS)
	$(Q)$(MKDIR) $(RESOURCE_EDIRS)
	$(Q)$(MKDIR) $(SRCDIRS)
CopyFile:
	$(Q)echo '1>' Ready to compiling ...
#	@echo '1>' Copying resources to $(RESOURCE_EDIRS) ...
	$(Q)cp -rf $(RESOURCE_SDIRS) $(RESOURCE_EDIRS)
#	@echo '1>' Copying sources to $(SRCDIRS) ...
#	$(Q)for name in $(SUBDIRS); do (cd $$name && $(CP) *.* $(cur_dir)/$(SRCDIRS)) done
	$(Q)for name in $(SUBDIRS); do (cd $$name && $(CP) *.* $(cur_dir)/$(SRCDIRS)) done
	$(Q)cd $(cur_dir)
Compile:
#	@echo '1>' Compiling sources in $(SRCDIRS) ...
	@echo '1>'---- Build started: Project: $(basename $(EXECNAME)), Configuration: Release Linux ----
	$(Q)make -s -C $(COMPILERDIRS)
	@echo
	@echo '1>'---- Config: $(notdir $(EXECDIRS)/$(EXECNAME)) - ARM linux apps Release ----
	@echo '1>' $(notdir $(EXECDIRS)/$(EXECNAME)) '- 0 error(s), 0 warning(s)'
	@echo
PrintInfo:
	@echo '1>' Executable file info: 
	@echo '1>' [dir]  : $(EXECDIRS)
	@cd $(EXECDIRS) && \
	 echo '1>' [name]: $(notdir $(EXECDIRS)/$(EXECNAME)) && \
	 echo '1>' [size]: && \
	 size -B $(notdir $(EXECDIRS)/$(EXECNAME)) && \
	cd $(top_dir)
EndTip :
	@echo
	@echo ///////////////////// End Make /////////////////////
	@echo
NODEP_yes:
	$(Q)cd $(COMPILERDIRS) && make NODEP=yes && cd $(top_dir)
objs:
	$(Q)$(MKDIR) $(SRCDIRS)
	$(Q)for name in $(SUBDIRS); do (cd $$name && $(CP) *.* $(cur_dir)/$(SRCDIRS)) done
	$(Q)cd $(cur_dir)
	$(Q)cd $(COMPILERDIRS) && make objs && cd $(top_dir)
tags:
	$(Q)cd $(COMPILERDIRS) && make tags && cd $(top_dir)
ctags:
	$(Q)cd $(COMPILERDIRS) && make ctags && cd $(top_dir)
	$(RM) $(EXECDIRS)/$(EXECNAME)
	$(RM) $(RESOURCE_EDIRS)/*
clean:
#	$(Q)cd $(COMPILERDIRS) && make clean && cd $(top_dir)
	$(RM) $(SRCDIRS)/*.*
	$(RM) $(EXECDIRS)/$(EXECNAME)
	$(RM) $(RESOURCE_EDIRS)/*
distclean:
	$(Q)cd $(COMPILERDIRS) && make distclean && cd $(top_dir)
show:
	$(Q)cd $(COMPILERDIRS) && make show && cd $(top_dir)
help:
	$(Q)cd $(COMPILERDIRS) && make help && cd $(top_dir)

# 
#
######################################################
