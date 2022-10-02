package practicce;

class Polynomial {
	double factor[] = new double[100];
	int degree[] = new int[100];
	int top;
	public Polynomial() {for (int i = 0; i < 100; i++) {
		degree[i] = 0;
		factor[i] = 0.0;
		top=0;
	}}
	public Polynomial(int a, int b[]) {
		for (int i = 0; i < 100; i++) {
			degree[i] = 0;
			factor[i] = 0.0;
		}
		top = a;
		for (int i = 0; i < top; i++) {
			degree[i] = top - i;
			
		}
		for(int i=0;i<b.length;i++) {
			factor[i]=b[i];
		}
	}

	void print_polynomial() {
		for (int i = 0; i < top; i++) {
			System.out.print(factor[i] + "x^" + degree[i] + '+');
		}
			System.out.println(factor[top]);
	}
}


public class Week_1 {
	static void add_poly(Polynomial A, Polynomial B) {
		int len;
		if (A.top > B.top) {
			len = A.top;
		} else if (A.top == B.top) {
			len = A.top;
		} else {
			len = B.top;
		}
		int p[] = { 0 };
		Polynomial ret = new Polynomial(len, p);
		ret.top = len;
		int c_index = 0;
		for (int i = c_index; i < len; i++) {
			for (int y = 0; y < len; y++) {
				if (A.degree[i] == B.degree[y]) {
					ret.factor[i] = A.factor[i] + B.factor[y];
					ret.degree[i] = A.degree[i];
					c_index++;
				} else if (A.degree[i] > B.degree[y]) {
					ret.degree[c_index] = A.degree[c_index];
					ret.factor[c_index] = A.degree[c_index];
					c_index++;
				} else if (A.degree[i] < B.degree[y]) {
					ret.degree[c_index] = B.degree[c_index];
					ret.factor[c_index] = B.degree[c_index];
					c_index++;
				}

			}

		}
		ret.factor[ret.top] = A.factor[A.top]+B.factor[B.top];

		ret.print_polynomial();
	}
	static void sub_poly(Polynomial A , Polynomial B) {
		int len;
		if (A.top > B.top) {
			len = A.top;
		} else if (A.top == B.top) {
			len = A.top;
		} else {
			len = B.top;
		}
		int p[] = { 0 };
		Polynomial ret = new Polynomial(len, p);
		ret.top = len;
		int c_index = 0;
		for (int i = c_index; i < len; i++) {
			for (int y = 0; y < len; y++) {
				if (A.degree[i] == B.degree[y]) {
					ret.factor[i] = A.factor[i] - B.factor[y];
					ret.degree[i] = A.degree[i];
					c_index++;
				} else if (A.degree[i] > B.degree[y]) {
					ret.degree[c_index] = A.degree[c_index];
					ret.factor[c_index] = A.degree[c_index];
					c_index++;
				} else if (A.degree[i] < B.degree[y]) {
					ret.degree[c_index] = B.degree[c_index];
					ret.factor[c_index] = B.degree[c_index];
					c_index++;
				}

			}

		}
		ret.factor[ret.top] = A.factor[A.top]-B.factor[B.top];
		ret.print_polynomial();
	}
	static void mult_poly(Polynomial A, Polynomial B) {
		System.out.println("mult");
		int index =0;
		Polynomial ret = new Polynomial();	
		ret.top = A.top*B.top;
		for(int i =0; i<=A.top;i++) {
			for(int y=0; y<=B.top;y++) {
				if(A.factor[i]>=0.0 && B.factor[y]>0.0) {
				ret.degree[index] = A.degree[i]+B.degree[y];
				ret.factor[index] = A.factor[i]*B.factor[y];
				index++;
				
				}
			}
			
		}
		System.out.println(B.factor[0]);
		for(int i=0; i<index;i++) {
			for(int y=0;y<index;y++) {
				if(y!=i) {
					if(ret.degree[i] == ret.degree[y]) {
						ret.factor[i] = ret.factor[i]+ret.factor[y];
						for(int z=y;z<index;z++) {
							ret.degree[z] = ret.degree[z+1];
							ret.factor[z] = ret.factor[z+1];
						}
						index--;
					}
				}
			}
		}
		ret.top =ret.degree[0];
		ret.print_polynomial();	
	}
	static void div_poly(Polynomial A,Polynomial B) {
		Polynomial ret = new Polynomial();
		ret.top = A.top-B.top;
		for(int i =ret.top;i>0;i--) {
			ret.factor[i] = A.factor[A.top]/B.factor[B.top];
			//ret.degree[i] = A.degree[i]-B.degree[i];
			
			for(int j=B.top;j>0;j--) {
				A.factor[i] -= ret.factor[i]*ret.factor[j];
				//A.degree[i] -= ret.degree[i]+B.degree[j];
				
			}
		}
		
		ret.print_polynomial();
	}
	public static void main(String []args) {
		int first[] = {3,6,0,0,0,10};
		int second[] = {7,0,5,0,1};
		Polynomial a= new Polynomial(5,first);
		a.print_polynomial();
		Polynomial b = new Polynomial(4, second);
		b.print_polynomial();
		System.out.println("--------------------------------");
		add_poly (a,b);
		System.out.println("result of minus ");
		sub_poly(a, b);
		System.out.println("--------------------------------");
		mult_poly(a, b);
		System.out.println("--------------------------------");
		int third[] = {2,-3,2,0};
		int fourth[] = {1,-1,-1};
		Polynomial c =new Polynomial(4,third);
		Polynomial d =new Polynomial(2,fourth);
		
		div_poly(c, d);
		
	}
}
