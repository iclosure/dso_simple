
�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[
�U       �q���������������������r       �U
�U       ���Z  �W�X�T�[�i�X�T�Y��       �U
�U       ���U  �U�U  �U�U�U    ��       �U
�U       ���^�T�a�`  �]�l�^�T�_��       �U
�U       �t���������������������s       �U
�U        Project : DSC--C-sources      �U
�U        Aurthor : L.K.H.              �U
�U        Version : V1.0                �U
�U        Data    : 09/20/2011          �U
�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a

    DSOWin.dsw -- VC6++����ִ���ļ�
    DSOWin.vcproj -- VS2008����ִ���ļ�

    ��VC6++��ֲVisual Studio 2008���������취�ܽ᣺
    
    1������ļ�����·����Project->Option->C/C++->General->���Ӱ���Ŀ¼��
    2������Զ�����ļ���Ҫ�� ����ļ�����·������ӿ��ļ�·����ͬʱ�ڣ�
       Project->Option->Linker->Input->��������������·�ļ�����(ע�⣬������׺)��
    3���������1>LINK : fatal error LNK1104: �޷����ļ���LIBC.lib����
       �� Project->Option->Linker->�����У��еĸ���ѡ������ӡ�/nodefaultlib:libc����
    4���������ϵͳ����:��Microsoft@Incremental Linker ��ֹͣ��������
       �� Project->Option->Linker->General�еġ������������ӡ���ֵ���ǡ���Ϊ���񡱡�
       ����ֱ�ӵ�����رճ��򡱺���F7���±��빤�̣��Ͳ����ٳ�����������ˡ�
    5�����Ǿ���������������޸ĺ󣬿��ع���������´���
       LINK : warning LNK4075: ���ԡ�/EDITANDCONTINUE��(���ڡ�/INCREMENTAL:NO���淶)
       �����������Ϊ��vc6�У�����ʹ�õ��������롣
 
       ����취��
           1) Project->Option->C/C++->General->�����������ӡ�ѡ����(INCREMENTAL)
       ����:
           2) ѡ����Ŀ Project->Option->C/C++  �޸� ������Ϣ��ʽ Ϊ �������ݿ⣨/zi�� 
    6��vs2008 warning C4819

       ����VC++�����ʱ�����������ʾ���棺

       warning C4819: The file contains a character that cannot be represented in the current code page (936). Save the file in Unicode format to prevent data loss

           ��Ϊֻ��һ��warning����Ӱ���������룬���Բ�û�������Ҷ��Ĺ�ע����һ��ʼ��ʱ��Ҳ����ˡ����Ǻ������ֵĴ������ˣ��������������ڳ���Debug��ʱ��
       �޷�ͣ�ڶϵ㣬ˢˢˢ�͹�ȥ�˸����޷�����Debug����������׾������warning�����������warning���ܽ���Debug�ˡ�

       ���潲��������ô�����������ġ�

           ����������˼�ǣ��ڸ��ļ�����һ�������ַ�����Unicode�ַ���Ҫ�������ַ����Unicode�ַ���

       ���⣺�ڱ�����Ϣ�ﲢû����ʾ���ĸ��ַ�������������һ������ֵĸ��ַ������������ǳ����ѣ������ǲ����ܵ�����

           �������������˺ö����϶�û���ҵ������������Ϊ��Ҷ���ע�������Ӱ�����ľ��档������һ���������վ���ҵ��˽���ķ������ܼ򵥣����������������Ҫ֪���������ĸ��ַ��ڵ���

       ����������򿪳���warning���ļ���Ctrl+Aȫѡ��Ȼ�����ļ��˵���file->advanced save options ���ڵ�����ѡ����ѡ���µı��뷽ʽΪ��UNICODE codepage 1200 �����ȷ��������ͽ���ˡ�
