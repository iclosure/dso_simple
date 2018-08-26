####################################################
#
#  ѡ���Ƿ��ӡ����
Q := @

#
# �����ܿ�Makefile���ڵ��ļ�·��
#
top_dir = $(PWD)/..
cur_dir = $(PWD)

###################################################
# ���������ļ�[Makefile]·��
COMPILERDIRS := ./compiler
####################################################
# Դ�ļ���ͷ�ļ��ݴ�·��
SRCDIRS      := ./src
export SRCDIRS 
#####################################################
#####################################################
# ���幤������������ļ���·��
EXECDIRS       := ./Output/bin
RESOURCE_EDIRS := ./Output
# 
# ���ղ����Ŀ�ִ���ļ���
EXECNAME       := dsolinx.bin
export EXECDIRS EXECNAME
#####################################################
#####################################################
# ���幤����Դ�ļ���·���б�
RESOURCE_SDIRS := $(top_dir)/resource

#####################################################
#####################################################
# ���幤���ļ���·���б�
#
##^##  ����Դ�ļ�·��
SUBDIRS := $(top_dir)/com
SUBDIRS += $(top_dir)/com/datatable
##^##  main ����������ļ�
SUBDIRS += $(top_dir)/main
##^##  dso ���ֵ��ļ�����Դ�ļ�·��
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
##^##  dsp ���ֵ��ļ�����Դ�ļ�·��
SUBDIRS += $(top_dir)/module/dsp/com
#SUBDIRS += $(top_dir)/module/dsp/src/datagen
#SUBDIRS += $(top_dir)/module/dsp/src/dataproc/fourier
SUBDIRS += $(top_dir)/module/dsp/src/dso_dsp
#SUBDIRS += $(top_dir)/module/dsp/src/dso_dsp/picproc
#SUBDIRS += $(top_dir)/module/dsp/src/external
##^##  gui ���ֵ��ļ�����Դ�ļ�·��
SUBDIRS += $(top_dir)/module/gui/antialias
SUBDIRS += $(top_dir)/module/gui/config
SUBDIRS += $(top_dir)/module/gui/core
SUBDIRS += $(top_dir)/module/gui/driver
SUBDIRS += $(top_dir)/module/gui/font
##^##  XXXX ���ֵ��ļ�����Դ�ļ�·��[�û�������]

#####################################################
#####################################################

# The command used to create file or file folder.
MKDIR  = mkdir -p
#######################################################################
# The command used to copy file.
#CP     = cp -u
CP     = cp -uf
# ������
# -a   ���൱�� -pdr ����˼��
# -d   ������Դ�ļ�Ϊ�����ļ�������(link file)�����������ļ����Զ��ǵ���������
# -f   ��Ϊǿ�� (force) ����˼�������ظ�����������ʱ������ѯ��ʹ���ߣ���ǿ�Ƹ��ƣ�
# -i   ����Ŀ�ęn(destination)�Ѿ�����ʱ���ڸ���ʱ����ѯ���Ƿ���Ķ�����
# -l   ������Ӳʽ���� (hard link) �����ᵵ���������Ǹ��Ƶ���������
# -p   ����ͬ����������һ���ƹ�ȥ������ʹ��Ԥ�����ԣ�
# -r   ���ݹ�������ƣ�����Ŀ¼�ĸ�����Ϊ��
# -s   �����Ƴ�Ϊ���������ļ� (symbolic link)���༴����ݷ�ʽ��������
# -u   ���� destination �� source �ɲŸ��� destination ��
# �����Ҫע��ģ������Դ�����������ϣ������һ��Ŀ���ļ�һ��Ҫ�ǡ�Ŀ¼�����У�
#######################################################################
# The command used to delete file.
RM     = -rm -rf

#
# �����Ŀ��
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