#include <cstdio>
#include <cstdlib>
int n, m, Card_top, cnt_F;
char Card[2005], tmp_s[5];
void Game_Finish(int win_kind);
struct Pig{
	static const int P = 4;
	int id, kind, pp, cnt, Last, Next;
	char card[2005], L[2005], R[2005], hd_K, hd_D, hd_P, tl_K, tl_D, tl_P;
	bool use_Z, jump_Z, jump_F, seem_F, dead, exist[2005];
	void get_card(){ // 摸牌
		card[++cnt] = Card[Card_top++], exist[cnt] = 1;
		if (card[cnt] == 'K') R[tl_K] = cnt, L[cnt] = tl_K, R[cnt] = 0, tl_K = cnt, !hd_K ? hd_K = cnt : 0;
		if (card[cnt] == 'D') R[tl_D] = cnt, L[cnt] = tl_D, R[cnt] = 0, tl_D = cnt, !hd_D ? hd_D = cnt : 0;
		if (card[cnt] == 'P') R[tl_P] = cnt, L[cnt] = tl_P, R[cnt] = 0, tl_P = cnt, !hd_P ? hd_P = cnt : 0;
	}
	bool show_G(int to_pig){ // 对to_pig献殷勤
		if (pig[to_pig].jump_F) if (kind != 3) return 0; else jump_F = 1;
		if (pig[to_pig].jump_Z) if (kind == 3) return 0; else jump_Z = 1;
		return 1;
	}
	bool show_H(int to_pig){ // 对to_pig表敌意
		if (pig[to_pig].jump_F) if (kind == 3) return 0; else jump_Z = 1;
		if (pig[to_pig].jump_Z) if (kind != 3) return 0; else jump_F = 1;
		return 1;
	}
	void DIE(int from_pig){ // 由于受到from_pig的伤害,该猪死亡
		if (use_P()) return ;
		dead = 1, pig[Last].Next = Next, pig[Next].Last = Last;
		if (kind == 1) Game_Finish(1);
		if (kind == 3) --cnt_F;
		if (!cnt_F) Game_Finish(0);
		if (kind == 3)
			for (register int i = 1; i <= 3; ++i) pig[from_pig].get_card();
		if (pig[from_pig].kind == 1){
			use_Z = 0;
			for (register int i = 1; i <= cnt; ++i) exist[i] = L[i] = R[i] = 0;
			cnt = hd_K = hd_D = hd_P = tl_K = tl_D = tl_P = 0;
		}
	}
	void del_pp(int from_pig){ // 受到来自from_pig的1伤害
		--pp;
		if (!pp) DIE(from_pig);
	}
	bool use_P(){ // 使用桃
		if (!hd_P || pp >= P) return 0;
		return exist[hd_P] = 0, hd_P = R[hd_P], ++pp, 1;
	}
	bool use_D(){ // 使用闪
		if (!hd_D) return 0;
		return exist[hd_D] = 0, hd_D = R[hd_D], 1;
	}
	bool use_K(){ // 使用杀
		if (!hd_K) return 0;
		return exist[hd_K] = 0, hd_K = R[hd_K], 1;
	}
	bool use_K(int to_pig){ // 对to_pig使用杀
		if (to_pig != Next) return 0;
		if (!show_H(to_pig)) return 0;

		if (pig[to_pig].use_D()) return 1;
		return pig[to_pig].del_pp(id), 1;
	}
	bool use_F(int to_pig){ // 对to_pig使用决斗
		if (!show_H(to_pig)) return 0;
		
	}
}pig[11];
void Game_Finish(int win_kind){
	if (win_kind == 0) printf("MP\n"); else printf("FP\n");
	for (register int i = 1; i <= n; ++i){
		if (pig[i].dead) { printf("DEAD\n"); continue; }
		for (register int j = 1; j <= pig[i].cnt; ++j)
			if (pig[i].exist[j]) putchar(pig[i].card[j]), putchar(' ');
		putchar('\n');
	}
	exit(0);
}