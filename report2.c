#include "gba1.h"

void draw_hp(point pa,point pb);//hp��`��

void draw_head(hword x,hword y,hword r);//����`��
void draw_body(point pa,point pb);//�̂�`��
void draw_arm(point pa,point pb);//�r��`��
void draw_hand(point pa,point pb);//���`��

void play(point hpa1,point hpb1,point hpa2,point hpb2,point arma1,point armb1,point arma2,point armb2,point handa1,point handb1,point handa2,point handb2);//�艟�����o������

void redraw_arm(hword,hword);//�r��`���Ȃ���
void redraw_hand(hword,hword);//���`���Ȃ���

void redraw_hp(hword,hword,hword);//hp��`������

void display_time(hword);//���Ԃ�\������

hword key;

int main (void){

	*((hword*)IOBASE) = 0x0F03;

	volatile unsigned short time;

	/* �^�C�}�J�E���^�ݒ背�W�X�^ */
	*((unsigned short *)0x04000100) = 0xFF00;	// �^�C�}0 �J�E���^�ݒ�(���N���b�N1/2^24�b ��60n�b)
	*((unsigned short *)0x04000104) = 0xFF00;	// �^�C�}1 �J�E���^�ݒ�(���N���b�N1/2^16�b ��15.4u�b)
	*((unsigned short *)0x04000108) = 0xFF00;	// �^�C�}2 �J�E���^�ݒ�(���N���b�N1/2^8�b  ��3.93m�b)
	*((unsigned short *)0x0400010C) = 0x0000;	// �^�C�}3 �J�E���^�ݒ�(���N���b�N1�b)

	/* �^�C�}���䃌�W�X�^ */	
	*((unsigned short *)0x04000102) = 0x0000;	// �^�C�}0 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hOFF�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x04000106) = 0x0004;	// �^�C�}1 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x0400010A) = 0x0004;	// �^�C�}2 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	*((unsigned short *)0x0400010E) = 0x0004;	// �^�C�}3 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j

	
	while(1){

		key=~(*(hword*)KEY_STATUS)&KEY_ALL;
	
		locate(1,1);
		prints("TEOSHIZUMO GAME ");
		locate(1,3);
		prints("This game for two people");
		locate(1,5);
		prints("1P A   :Avoid  B   :Attack");
		locate(1,7);
		prints("2P LEFT:Attack RIGHT:Avoid");
		locate(7,11);
		prints("Let's start:Push A");
	

		if(key==KEY_A){

			point hpPa1,hpPb1;
			hpPa1.x = 10;
			hpPa1.y = 10;
			hpPb1.x = 109;
			hpPb1.y = 24;

			point hpPa2,hpPb2;
			hpPa2.x = 239-hpPb1.x;
			hpPa2.y = hpPa1.y;
			hpPb2.x = 239-hpPa1.x;
			hpPb2.y = hpPb1.y;
	
			hword headX1 = 85;
			hword headY1 = 90;
			hword headR1 = 10;

			hword headX2 = 239-headX1;
			hword headY2 = headY1;
			hword headR2 = headR1;
	
			point bodyPa1,bodyPb1;
			bodyPa1.x = 75;
			bodyPa1.y = 100;
			bodyPb1.x = 94;
			bodyPb1.y = 149;

			point bodyPa2,bodyPb2;
			bodyPa2.x = 239-bodyPb1.x;
			bodyPa2.y = bodyPa1.y;
			bodyPb2.x = 239-bodyPa1.x;
			bodyPb2.y = bodyPb1.y;
	
			point armPa1,armPb1;
			armPa1.x = 95;
			armPa1.y = 105;
			armPb1.x = 109;
			armPb1.y = 114;

			point armPa2,armPb2;
			armPa2.x = 239-armPb1.x;
			armPa2.y = armPa1.y;
			armPb2.x = 239-armPa1.x;
			armPb2.y = armPb1.y;

			point handPa1,handPb1;
			handPa1.x = 110;
			handPa1.y = 100;
			handPb1.x = 114;
			handPb1.y = 114;

			point handPa2,handPb2;
			handPa2.x = 239-handPb1.x;
			handPa2.y = handPa1.y;
			handPb2.x = 239-handPa1.x;
			handPb2.y = handPb1.y;

			hword i;
			hword j;
			for(i=0;i<240;i++){
				for(j=0;j<160;j++){
					draw_point(i,j,BGR(0x00,0x00,0x00));
				}
			}
	
			draw_hp(hpPa1,hpPb1);
			draw_hp(hpPa2,hpPb2);

			draw_head(headX1,headY1,headR1);
			draw_head(headX2,headY2,headR2);
	
			draw_body(bodyPa1,bodyPb1);
			draw_body(bodyPa2,bodyPb2);
	
			draw_arm(armPa1,armPb1);
			draw_arm(armPa2,armPb2);

			draw_hand(handPa1,handPb1);
			draw_hand(handPa2,handPb2);

			locate(4,15);
			prints("1P");

			locate(25,15);
			prints("2P");

			play(hpPa1,hpPb1,hpPa2,hpPb2,armPa1,armPb1,armPa2,armPb2,handPa1,handPb1,handPa2,handPb2);
			
			locate(9,8);
			prints("Skip:Push START");
		
			*((unsigned short *)0x04000102) = 0x0080;	// �^�C�}0 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hOFF�C�v���X�P�[���Ȃ��j
			*((unsigned short *)0x04000106) = 0x0084;	// �^�C�}1 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
			*((unsigned short *)0x0400010A) = 0x0084;	// �^�C�}2 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
			*((unsigned short *)0x0400010E) = 0x0084;	// �^�C�}3 ����ݒ�i�^�C�}ON�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	
			while(time<10){

				key=~(*(hword*)KEY_STATUS)&KEY_ALL;
	
		
				//* �^�C�}3 �J�E���g�l�Ǎ��� */
				time = *((unsigned short *)0x0400010C);
		
				/* time �\���ʒu�ݒ� */
				locate(14, 7);
				display_time(10-time);
		
				if(key==KEY_START){
					break;
				}
			}

			time=0;
		
			*((unsigned short *)0x04000102) = 0x0000;	// �^�C�}0 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hOFF�C�v���X�P�[���Ȃ��j
			*((unsigned short *)0x04000106) = 0x0004;	// �^�C�}1 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
			*((unsigned short *)0x0400010A) = 0x0004;	// �^�C�}2 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
			*((unsigned short *)0x0400010E) = 0x0004;	// �^�C�}3 ����ݒ�i�^�C�}OFF�C������OFF�C�J�X�P�[�hON�C�v���X�P�[���Ȃ��j
	
			hword k;
			hword m;
			for(k=0;k<240;k++){
				for(m=0;m<160;m++){
					draw_point(k,m,BGR(0x00,0x00,0x00));
				}
	
			}
		}
	}
	return 0;
}

void draw_hp(point pa,point pb){

	hword i;
	hword j;
	for(i=pa.x;i<=pb.x;i++){
		for(j=pa.y;j<=pb.y;j++){
			draw_point(i,j,BGR(0x00,0x1F,0x00));
		}
	}
}

void draw_head(hword x,hword y,hword r){
	
	hword i;
	hword j;
	for(i=0;i<240;i++){
		for(j=0;j<160;j++){
			if((i-x)*(i-x)+(j-y)*(j-y)<=r*r){
				draw_point(i,j,BGR(0x1F,0x1F,0x1F));
			}
		}
	}
}

void draw_body(point pa,point pb){

	hword i;
	hword j;
	for(i=pa.x;i<=pb.x;i++){
		for(j=pa.y;j<=pb.y;j++){
			draw_point(i,j,BGR(0x1F,0x1F,0x1F));
		}
	}
}

void draw_arm(point pa,point pb){

	hword i;
	hword j;
	for(i=pa.x;i<=pb.x;i++){
		for(j=pa.y;j<=pb.y;j++){
			draw_point(i,j,BGR(0x1F,0x1F,0x1F));
		}
	}
}

void draw_hand(point pa,point pb){

	hword i;
	hword j;
	for(i=pa.x;i<=pb.x;i++){
		for(j=pa.y;j<=pb.y;j++){
			draw_point(i,j,BGR(0x1F,0x1F,0x1F));
		}
	}
}

void play(point hpa1,point hpb1,point hpa2,point hpb2,point arma1,point armb1,point arma2,point armb2,point handa1,point handb1,point handa2,point handb2){

	hword attackFlag1=0;//1P�̍U���t���O
	hword attackFlag2=0;//2P�̍U���t���O

	while(1){

		key=~(*(hword*)KEY_STATUS)&KEY_ALL;
		
		if((handb1.x==handa2.x-2)&&attackFlag2==1){//2P��1P�ɍU��������1P��HP������

			hword a=hpb1.x;
			hpb1.x=hpb1.x-10;

			if(hpb1.x<30){//1P��HP�������Ă�����HP��ԐF�ɕύX
				redraw_hp(hpa1.x,a,BGR(0x1F, 0, 0));
			}

			redraw_hp(hpb1.x,a,BGR(0, 0, 0));

			if(hpb1.x<=hpa1.x){//HP���Ȃ��Ȃ�Ό��ʂ̕������o���A���̊֐����I������
				locate(13,5);
				prints("2P WIN");
				return ;
			}

			attackFlag2=0;
		}

		if((handb1.x==handa2.x-2)&&attackFlag1==1){//1P��2P�ɍU��������2P��HP������

			hword a=hpa2.x;
			hpa2.x=hpa2.x+10;

			if(hpa2.x>209){//2P��HP�������Ă�����HP��ԐF�ɕύX
				redraw_hp(a,hpb2.x,BGR(0x1F, 0, 0));
			}

			redraw_hp(a,hpa2.x,BGR(0, 0, 0));
			if(hpa2.x>=hpb2.x){//HP���Ȃ��Ȃ�Ό��ʂ̕������o���A���̊֐����I������

				locate(13,5);
				prints("1P WIN");
				return ;
			}

			attackFlag1=0;
		}

		if((key==KEY_B||key==(KEY_B|KEY_RIGHT))&&armb1.x<119){//1P���U�����Ă��邩�QP���U�����Ă��Ȃ��Ƃ�

			redraw_hand(handa1.x,BGR(0, 0, 0));

			armb1.x=armb1.x+1;
			handa1.x=handa1.x+1;
			handb1.x=handb1.x+1;
			
			redraw_arm(armb1.x,BGR(0x1F,0x1F,0x1F));
			redraw_hand(handb1.x,BGR(0x1F,0x1F,0x1F));

			attackFlag1=1;//�U������

			hword i;
			hword j;
			if(armb1.x==119){//�ړ����x����

				for(i=0;i<1000;i++){
					for(j=0;j<100;j++){}
				}

				hword a=hpb1.x;
				hpb1.x=hpb1.x-1;//1P��HP������

				if(hpb1.x<30){//1P��HP�������Ă�����HP��ԐF�ɕύX
					redraw_hp(hpa1.x,a,BGR(0x1F, 0, 0));
				}

				redraw_hp(hpb1.x,a,BGR(0, 0, 0));

				if(hpb1.x<=hpa1.x){//HP���Ȃ��Ȃ�Ό��ʂ̕������o���A���̊֐����I������
					locate(13,5);
					prints("2P WIN");
					return ;
				}

				attackFlag1=0;
			}

		}else if(armb1.x>109){//�PP���U������߂��̎��A�r�����̈ʒu�܂ł��ǂ�

			redraw_hand(handb1.x,BGR(0, 0, 0));
			redraw_arm(armb1.x,BGR(0, 0, 0));

			armb1.x=armb1.x-1;
			handa1.x=handa1.x-1;
			handb1.x=handb1.x-1;

			redraw_hand(handa1.x,BGR(0x1F,0x1F,0x1F));
			
			attackFlag1=0;
		}

		if((key==KEY_A||key==(KEY_A|KEY_LEFT)||key==(KEY_A|KEY_RIGHT))&&armb1.x>99){//���̈ʒu��Z���������Ƃ��r���k�߂�

			redraw_hand(handb1.x,BGR(0, 0, 0));
			redraw_arm(armb1.x,BGR(0, 0, 0));

			armb1.x=armb1.x-1;
			handa1.x=handa1.x-1;
			handb1.x=handb1.x-1;

			redraw_hand(handa1.x,BGR(0x1F,0x1F,0x1F));
			
		}else if((key==KEY_A||key==(KEY_A|KEY_LEFT)||key==(KEY_A|KEY_RIGHT))&&armb1.x==99){
			
		}else if(armb1.x<109){//Z���͂Ȃ����Ƃ��r����̈ʒu�܂Ŗ߂�
			redraw_hand(handa1.x,BGR(0, 0, 0));

			armb1.x=armb1.x+1;
			handa1.x=handa1.x+1;
			handb1.x=handb1.x+1;

			redraw_arm(armb1.x,BGR(0x1F,0x1F,0x1F));
			redraw_hand(handb1.x,BGR(0x1F,0x1F,0x1F));
			
		}

		if((key==KEY_LEFT||key==(KEY_LEFT|KEY_A))&&arma2.x>120){

			redraw_hand(handb2.x,BGR(0, 0, 0));

			arma2.x=arma2.x-1;
			handb2.x=handb2.x-1;
			handa2.x=handa2.x-1;

			redraw_arm(arma2.x,BGR(0x1F,0x1F,0x1F));
			redraw_hand(handa2.x,BGR(0x1F,0x1F,0x1F));
			
			attackFlag2=1;

			hword i;
			hword j;

			if(arma2.x==120){

				for(i=0;i<1000;i++){
					for(j=0;j<100;j++){}
				}

				hword a=hpa2.x;
				hpa2.x=hpa2.x+1;

				if(hpa2.x>209){
					redraw_hp(a,hpb2.x,BGR(0x1F, 0, 0));
				}

				redraw_hp(a,hpa2.x,BGR(0, 0, 0));

				if(hpa2.x==hpb2.x){

				locate(13,5);
				prints("1P WIN");
				return ;
				}

				attackFlag2=0;
			}

		}else if(arma2.x<130){

			redraw_hand(handa2.x,BGR(0, 0, 0));
			redraw_arm(arma2.x,BGR(0, 0, 0));

			arma2.x=arma2.x+1;
			handb2.x=handb2.x+1;
			handa2.x=handa2.x+1;

			redraw_hand(handb2.x,BGR(0x1F,0x1F,0x1F));
			
			attackFlag2=0;
		}

		if((key==KEY_RIGHT||key==(KEY_RIGHT|KEY_A)||key==(KEY_RIGHT|KEY_B))&&arma2.x<140){

			redraw_hand(handa2.x,BGR(0, 0, 0));
			redraw_arm(arma2.x,BGR(0, 0, 0));

			arma2.x=arma2.x+1;
			handb2.x=handb2.x+1;
			handa2.x=handa2.x+1;

			redraw_hand(handb2.x,BGR(0x1F,0x1F,0x1F));
			
		}else if((key==KEY_RIGHT||key==(KEY_RIGHT|KEY_A)||key==(KEY_RIGHT|KEY_B))&&arma2.x==140){

		}else if(arma2.x>130){

			redraw_hand(handb2.x,BGR(0, 0, 0));

			arma2.x=arma2.x-1;
			handb2.x=handb2.x-1;
			handa2.x=handa2.x-1;	

			redraw_arm(arma2.x,BGR(0x1F,0x1F,0x1F));
			redraw_hand(handa2.x,BGR(0x1F,0x1F,0x1F));
			
		}

	}

}

void redraw_arm(hword x,hword color){

	hword i;
	for(i=105;i<=114;i++){
			draw_point(x,i,color);
	}
}

void redraw_hand(hword x,hword color){

	hword i;
	for(i=100;i<=114;i++){
			draw_point(x,i,color);
	}
}

void redraw_hp(hword x1,hword x2,hword color){

	hword i;
	hword j;
	for(i=10;i<=24;i++){
		for(j=x1;j<=x2;j++){
			draw_point(j,i,color);
		}
	}
}

void display_time(hword val) {
	
	
/* ������10�i���Ƃ��ĕ\������֐��i�ő�l16�r�b�g�j*/

	byte char_data[] = "0123456789";
	byte buf[6];
	hword tmp;
	int i;
	
	/* ���͒lval�̌����ݒ� */
	i = 3;

	/* ������̍Ō��NULL�R�[�h�}�� */
	buf[i+1] = 0;
	
	/* �ŉ��ʌ��̕����i10�Ŋ������]��j��}�����C���͒l��10�Ŋ��� */
	for(; i >= 0; i--) {
		buf[i] = char_data[mod(val, 10)];
		val = div(val, 10);
	}
	
	/* ������S�̂�\�� */
	prints(buf);
	
	return;
}
