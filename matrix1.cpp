using namespace std;
class matrix
{
private:
	int n, m;
	double** a;
public:
	static double eps;
	matrix();
	matrix(int n, int m, double** a);
	matrix(const matrix& m2); 
	~matrix();
	double& operator()(int row, int col);
	void operator()(int row, int col, double val);
	matrix& operator= (const matrix& m2);
	matrix operator + (matrix m2);
	matrix operator - (matrix m2);
	matrix operator * (matrix m2);
	matrix operator * (double x);
	matrix operator / (double x);
	bool operator == (matrix m2);
	bool operator != (matrix m2);
	int sled();
	friend std::ostream& operator<< (ostream& out, const matrix& m);
};
ostream& operator<< (ostream& out, const matrix& m)
{

	for (int i = 0; i < m.n; i++)
	{
		for (int j = 0; j < m.m; j++)
			out << m.a[i][j] << "\t";
		out << endl;
	}

	return out;
}
matrix::~matrix()
{

	for (int i = 0; i < n; i++)
		delete[]a[i];
	delete[]a;
}
matrix::matrix()
{

}
matrix::matrix(int n, int m, double** a)
{
	
	this->n = n;
	this->m = m;
	this->a = new double* [n];
	for (int i = 0; i < n; i++)
		this->a[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			this->a[i][j] = a[i][j];
}
matrix::matrix(const matrix& m2)
{
	
	this->n = m2.n;
	this->m = m2.m;
	this->a = new double* [n];
	for (int i = 0; i < n; i++)
		this->a[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			this->a[i][j] = m2.a[i][j];
}
matrix& matrix::operator =(const matrix& m2)
{
	
	this->n = m2.n;
	this->m = m2.m;
	this->a = new double* [n];
	for (int i = 0; i < n; i++)
		this->a[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			this->a[i][j] = m2.a[i][j];
	return *this;
}
double& matrix::operator()(int row, int col)
{
	
	if (row < 0 || row >= n || col < 0 || col >= m)
		throw - 2;
	return a[row][col];
}
void matrix::operator()(int row, int col, double val)
{
	
	if (row < 0 || row >= n || col < 0 || col >= m)
		throw - 2;
	a[row][col] = val;
}
bool matrix::operator == (matrix m2)
{
	if (n != m2.n || m != m2.m)
		return false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (fabs(a[i][j] - m2.a[i][j]) > eps * fmax(fabs(a[i][j]), fabs(m2.a[i][j])))
				return false;
	return true;
}
bool matrix::operator != (matrix m2)
{
	if (n != m2.n || m != m2.m)
		return true;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (fabs(a[i][j] - m2.a[i][j]) > eps * fmax(fabs(a[i][j]), fabs(m2.a[i][j])))
			{
				return true;
			}
	return false;
}
matrix matrix::operator + (matrix m2)
{
	if (n != m2.n || m != m2.m)
		throw - 1;
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
		c[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = a[i][j] + m2.a[i][j];
	matrix z(n, m, c);
	return z;

}
matrix matrix::operator - (matrix m2)
{
	if (n != m2.n || m != m2.m)
		throw - 1;
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
		c[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = a[i][j] - m2.a[i][j];
	matrix z(n, m, c);
	return z;
}
matrix matrix::operator * (matrix m2)
{
	if (n != m2.m)
		throw - 1;
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
	{
		c[i] = new double[m2.m];
		for (int j = 0; j < m2.m; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < m; k++)
				c[i][j] += a[i][k] * m2.a[k][j];
		}
	}
	matrix z(n, m2.m, c);
	return z;
}
matrix matrix::operator * (double x)
{
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
		c[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = a[i][j] * x;
	matrix z(n, m, c);
	return z;
}
matrix matrix::operator / (double x)
{
	if (x == 0)
		throw - 3;
	double** c = new double* [n];
	for (int i = 0; i < n; i++)
		c[i] = new double[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = a[i][j] / x;
	matrix z(n, m, c);
	return z;
}
int matrix::sled()
{
	int trace = 0; 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (i == j)
				trace += a[i][j]; 
	return trace;
}
double matrix::eps = 0.000001;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, m;
	int col, row;
	double elem;
	double** a;
	cout << "Введите количество строк в первой матрице" << endl;
	cin >> n;
	cout << "Введите количество столбцов в первой матрице" << endl;
	cin >> m;
	a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[m];
	cout << "Введите элементы первой матрицы" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cout << "a[" << i << "][" << j << "]=";
			cin >> a[i][j];
		}
	matrix m1(n, m, a);
	cout << "Введите количество строк во второй матрице" << endl;
	cin >> n;
	cout << "Введите количество стролбцов во второй матрице" << endl;
	cin >> m;
	a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[m];
	cout << "Введите элементы второй матрицы" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cout << "a[" << i << "][" << j << "]=";
			cin >> a[i][j];
		}
	matrix m2(n, m, a);
	cout << "Исходные матрицы" << endl;
	cout << m1 << endl;
	cout << m2 << endl;
	if (m1 == m2)
		cout << "Матрицы равны" << endl;
	else cout << "Матрицы не равны" << endl;
	try
	{
		cout << "Доступ к элементам по индеку:" << endl;
		cout << "Введите номер строки" << endl;
		cin >> col;
		cout << "Введите номер стролба" << endl;
		cin >> row;
		cout << m1(col, row) << endl;
		cout << "Введите элемент для замены" << endl;
		cin >> elem;
		m1(col, row, elem); 
		cout << m1 << endl;
	}
	catch (int err)
	{
		cout << "Индекс находится за пределами размерностей" << endl;
	}
	cout << "След матрицы 1" << endl;
	cout << m1.sled() << endl;
	cout << "След матрицы 2" << endl;
	cout << m2.sled() << endl;
	try
	{
		cout << "Результат сложения матриц" << endl;
		cout << m1 + m2 << endl;
		cout << "Результат вычитания матриц" << endl;
		cout << m1 - m2 << endl;
	}
	catch (int err)
	{
		cout << "Размерности не совпадают" << endl;
	}
	try
	{
		cout << "Результат умножения матриц" << endl;
		cout << m1 * m2 << endl;
	}
	catch (int err)
	{
		cout << "Размерности не удовлетворяют правилам умножения" << endl;
	}
	double scalar;
	cout << "Введите скаляр для операций над матрицами" << endl;
	cin >> scalar;
	cout << "Результат умножения матрицы на скаляр" << endl;
	cout << m1 * scalar << endl;
	cout << "Результат деления матрицы на скаляр" << endl;
	cout << m1 / scalar << endl;
	system("pause");
	return 0;
}

