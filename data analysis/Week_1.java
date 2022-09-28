package Homework;

class Polynomial {
	double factor[] = new double[100];
	int degree[] = new int[100];
	int top;

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
		
	}
}
