#include "pch.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <array>
#include "cpplinq.hpp"
using namespace std;
using namespace cpplinq;


//--------------------------------------------------------------------------
// 要素の取得
void sampleFunc00()
{
	int _Src[] = {41, 20, 6, 12, 33, 6};

	// first : 条件を満たす最初の要素を取り出す。
	auto _Ret1 = from_array(_Src)
		>> first([](int x) { return(x % 2 == 0); });
	
	printf("first = %d\n", _Ret1);

	// first_or_default : 最初の要素、またはデフォルト値を取得する。
	auto _Ret2 = from_array(_Src)
		>> first_or_default([](int x) { return(x > 99); });

	printf("first_or_default = %d\n", _Ret2);

	// last_or_default : 最後の要素、またはデフォルト値を取得する。
	auto _Ret3 = from_array(_Src)
		>> last_or_default([](int x) {return(x % 2 == 0); });

	printf("last_or_default = %d\n", _Ret3);


	int _Src2[] = { 1, 2, 3, 99, 30, 20, 10, 99, 5 };

	// where : 条件を満たす要素を抽出する。
	auto _Ret4 = from_array(_Src2)
		>> where([](int x) {return(x > 10); })
		>> to_vector();
	printf("where = ");	for (auto& _It : _Ret4) { printf("%d, ", _It); } printf("\n");

	// distinct : 重複を取り除く。
	auto _Ret5 = from_array(_Src2)
		>> distinct()
		>> to_vector();
	printf("distinct = ");	for (auto& _It : _Ret5) { printf("%d, ", _It);  } printf("\n");

	// skip : 先頭から指定数の要素をスキップして残りを返す。
	auto _Ret6 = from_array(_Src2)
		>> skip(5)
		>> to_vector();
	printf("skip = ");	for (auto& _It : _Ret6) { printf("%d, ", _It); } printf("\n");

	// skip_while : 先頭から指定条件を満たさなくなるまでスキップし残りを返す。
	auto _Ret7 = from_array(_Src2)
		>> skip_while([](int x) {return(x <= 10); })
		>> to_vector();
	printf("skip_while = ");	for (auto& _It : _Ret7) { printf("%d, ", _It); } printf("\n");

	// take : 先頭から指定数の要素を返す。
	auto _Ret8 = from_array(_Src2)
		>> take(5)
		>> to_vector();
	printf("take = ");	for (auto& _It : _Ret8) { printf("%d, ", _It); } printf("\n");

	// take_while : 先頭から指定条件を満たす要素を返す。（条件を満たさない以降の要素は返さない）
	auto _Ret9 = from_array(_Src2)
		>> take_while([](int x) {return(x <= 10); })
		>> to_vector();
	printf("take_while = ");	for (auto& _It : _Ret9) { printf("%d, ", _It); } printf("\n");


}


//--------------------------------------------------------------------------
// 要素の作成
void sampleFunc01()
{
	// singleton : この演算子は、引数として指定された単一の要素で範囲を作成します。
	auto _Ret1 = singleton(10)
		>> to_vector();
	printf("singleton = %d\n", _Ret1.at(0));	 // => {10}


	// generate : 入力されたラムダ式から範囲を作成します。
	auto x = -1;
	auto _Ret2 = generate([&]() {return (++x < 3) ? to_opt(x) : to_opt<int>(); }) 
		>> to_vector();
	printf("generate = ");	for (auto& _It : _Ret2) { printf("%d, ", _It); } printf("\n");	 // => {0,1,2}


	// pairwise : 入力範囲の隣接する要素をグループ化して、新しい範囲のペアを生成します。 
	int numbers[] = { 1, 2, 3, 4, 5 };
	auto _Ret3 = from_array(numbers) 
		>> pairwise() 
		>> to_vector();
	printf("pairwise = \n");	for (auto& _It : _Ret3) { printf("(%d, %d)\n", get<0>(_It), get<1>(_It)); } printf("\n");	 // => {(1,2),(2,3),(3,4),{4,5}}


	// zip_with : 2つの異なる範囲から要素をグループ化して新しい範囲のペアを生成します。サイズが異なる場合、結果は最小範囲のサイズになります。
	int a[] = { 1, 2, 3 };
	string b[] = { "one", "two", "three", "four", "five" };
	auto _Ret4 = from_array(a) 
		>> zip_with(from_array(b)) 
		>> to_vector();
	printf("zip_with = \n");	for (auto& _It : _Ret4) { printf("(%d, %s)\n", get<0>(_It), get<1>(_It).c_str()); } printf("\n");	 // => {(1,"one"), (2,"two"), (3,"three")}

}


//--------------------------------------------------------------------------
// 集計
void sampleFunc02()
{
	int _Src[] = {5, 7, 11, 2, 6, 10};

	// max : 最大値を取得する
	auto _Ret1 = from_array(_Src)
		>> max();
	printf("max = %d\n", _Ret1);

	// min : 最小値を取得する
	auto _Ret2 = from_array(_Src)
		>> min();
	printf("min = %d\n", _Ret2);

	// avg : 平均を取得する
	auto _Ret3 = from_array(_Src)
		>> avg();
	printf("avg = %d\n", _Ret3);

	// sum : 合計を取得する
	auto _Ret4 = from_array(_Src)
		>> sum();
	printf("sum = %d\n", _Ret4);

	// count : 要素数を取得する
	auto _Ret5 = from_array(_Src)
		>> count();
	printf("count = %d\n", _Ret5);

	// aggregate : アキュムレーター関数で計算した結果を取得する
	printf("aggregate = ");
	auto _Ret6 = from_array(_Src)
		>> aggregate(0, [](int a, int b) { printf("(%d, %d)->", a, b); return(a + b); });
	printf(" = %d\n", _Ret6);

}


//--------------------------------------------------------------------------
// 判定
void sampleFunc03()
{
	int _Src[] = { 1, 2, 3, 4, 5, 6 };
	int _Src2[] = { 2, 3, 4, 5, 6, 1 };

	// all : 全ての要素が条件を満たしているか判定する
	auto _Ret1 = from_array(_Src)
		>> all([](int x) {return(x >= 5); });
	printf("all : %d\n", _Ret1);

	// any : 条件を満たす要素が含まれているか判定する
	auto _Ret2 = from_array(_Src)
		>> any([](int x) {return(x >= 5); });
	printf("any = %d\n", _Ret2);

	// contains : 指定した要素が含まれているか判定する
	auto _Ret3 = from_array(_Src)
		>> contains(0);
	printf("contains = %d\n", _Ret3);

	// sequence_equal : 2つのシーケンスが等しいか判定する
	auto _Ret4 = from_array(_Src)
		>> sequence_equal(from_array(_Src2));
	printf("sequence_equal = %d\n", _Ret4);

}

//--------------------------------------------------------------------------
// 集合
void sampleFunc04()
{
	int _Src1[] = { 1, 2, 3, 10, 20 };
	int _Src2[] = { 0, 2, 4, 10, 11 };

	// union_with : 和集合を求める。
	auto _Ret1 = from_array(_Src1)
		>> union_with(from_array(_Src2))
		>> to_vector();
	printf("_Ret1 = ");	for (auto& _It : _Ret1) { printf("%d, ", _It); } printf("\n");

	// except : 差集合を求める。
	auto _Ret2 = from_array(_Src1)
		>> except(from_array(_Src2))
		>> to_vector();
	printf("_Ret2 = ");	for (auto& _It : _Ret2) { printf("%d, ", _It); } printf("\n");

	auto _Ret3 = from_array(_Src2)
		>> except(from_array(_Src1))
		>> to_vector();
	printf("_Ret3 = ");	for (auto& _It : _Ret3) { printf("%d, ", _It); } printf("\n");

	// intersect_with : 積集合を求める。
	auto _Ret4 = from_array(_Src1)
		>> intersect_with(from_array(_Src2))
		>> to_vector();
	printf("_Ret4 = ");	for (auto& _It : _Ret4) { printf("%d, ", _It); } printf("\n");
	
}


//--------------------------------------------------------------------------
// ソート
void sampleFunc05()
{
	class CData {
	public:
		int Id;
		string Name;
		
		CData(int _Id, string _Name):Id(_Id), Name(_Name){}
	};

	auto _Data = list<CData>{
		{CData(0, "alpha")},
		{CData(1, "beta")},
		{CData(3, "delta")},
		{CData(1, "gamma")},
	};

	// orderby_ascending : 要素を昇順にソートする。
	auto _Ret1 = from(_Data)
		>> orderby_ascending([](CData x) {return(x.Id); })
		>> thenby_descending([](CData x) {return(x.Name.length()); })
		>> to_list();
	printf("_Ret1 = \n");	for (auto& _It : _Ret1) { printf("{%d, %s}\n", _It.Id, _It.Name.c_str()); } printf("\n");

	// thenby_ascending : ソートした要素に対し、キーが等しい要素を昇順にソートする。
	// thenby_descending :　ソートした要素に対し、キーが等しい要素を降順にソートする。 
	auto _Ret2 = from(_Data)
		>> orderby_ascending([](CData x) {return(x.Id); })
		>> thenby_descending([](CData x) {return(x.Name.length()); })
		>> to_list();
	printf("_Ret2 = \n");	for (auto& _It : _Ret2) { printf("{%d, %s}\n", _It.Id, _It.Name.c_str()); } printf("\n");

	// orderby_descending : 要素を降順にソートする。
	auto _Ret3 = from(_Data)
		>> orderby_descending([](CData x) {return(x.Id); })
		>> to_list();
	printf("_Ret3 = \n");	for (auto& _It : _Ret3) { printf("{%d, %s}\n", _It.Id, _It.Name.c_str()); } printf("\n");

	// reverse : 要素を逆順にソートする。
	auto _Ret4 = from(_Data)
		>> reverse()
		>> to_list();
	printf("_Ret4 = \n");	for (auto& _It : _Ret4) { printf("{%d, %s}\n", _It.Id, _It.Name.c_str()); } printf("\n");

}


//--------------------------------------------------------------------------
// 射影
void sampleFunc06()
{
	class CData {
	public:
		int Id;
		string Name;

		CData(int _Id, string _Name) :Id(_Id), Name(_Name) {}
	};

	auto _Data = list<CData>{
		{CData(0, "aaa")},
		{CData(1, "bbb")},
		{CData(2, "ccc")},
		{CData(3, "ddd")},
	};

	// select : 1つの要素を単一の要素に射影する。
	auto _Ret1 = from(_Data)
		>> select([](const auto& x) {return(x.Id + 10); })
		>> to_list();
	printf("_Ret1 = ");	for (auto& _It : _Ret1) { printf("%d, ", _It); } printf("\n");

	
	// select_many : 1つの要素から複数の要素に射影し、その結果を1つのシーケンスで返す。
	auto _Ret2 = from(_Data)
		>> select_many([](const auto& x) {
		auto _dst = vector<int>{ x.Id, x.Id * 10 };
		return(from_copy(_dst));
		})
		>> to_list();
	printf("_Ret2 = ");	for (auto& _It : _Ret2) { printf("%d, ", _It); } printf("\n");

}


//--------------------------------------------------------------------------
// 結合
void sampleFunc07()
{
	class CData1 {
	public:
		string Name;
		int Param1;

		CData1(string _Name, int _Param) :Name(_Name), Param1(_Param) {}
	};
	class CData2 {
	public:
		string Name;
		string Param2;

		CData2(string _Name, string _Param) :Name(_Name), Param2(_Param) {}
	};

	auto _Outer1 = list<CData1>{
		{CData1("aaa", 10)},
		{CData1("bbb", 11)},
		{CData1("ccc", 12)},
	};
	auto _Outer2 = list<CData1>{
		{CData1("ddd", 20)},
		{CData1("eee", 30)},
	};
	auto _Inner = list<CData2>{
		{CData2("aaa", "alpha")},
		{CData2("bbb", "beta")},
		{CData2("ddd", "delta")},
		{CData2("aaa", "epsilon")},
	};


	// join : 内部結合を行ったシーケンスを返す。
	auto _Ret1 = from(_Outer1)
		>> join(from(_Inner),
			[](const auto& o) {return(o.Name); },
			[](const auto& i) {return(i.Name); },
			[](const auto& o, const auto& i) {return(make_tuple(o.Name, o.Param1, i.Param2)); })
		>> to_list();
	printf("_Ret1 = \n");	for (auto& _It : _Ret1) { printf("{%s, %d, %s}\n", get<0>(_It).c_str(), get<1>(_It), get<2>(_It).c_str() ); } printf("\n");


	// concat : 2つのシーケンスを連結する。
	auto _Ret2 = from(_Outer1)
		>> concat(from(_Outer2))
		>> to_list();
	printf("_Ret2 = \n");	for (auto& _It : _Ret2) { printf("{%s, %d}\n", _It.Name.c_str(), _It.Param1); } printf("\n");

}


//==========================================================================
// メイン
int main()
{
	printf("■要素の取得-----------\n");
	sampleFunc00();
	printf("\n\n");

	printf("■要素の作成-----------\n");
	sampleFunc01();
	printf("\n\n");

	printf("■集計-----------\n");
	sampleFunc02();
	printf("\n\n");

	printf("■判定-----------\n");
	sampleFunc03();
	printf("\n\n");

	printf("■集合-----------\n");
	sampleFunc04();
	printf("\n\n");

	printf("■ソート-----------\n");
	sampleFunc05();
	printf("\n\n");

	printf("■射影-----------\n");
	sampleFunc06();
	printf("\n\n");

	printf("■結合-----------\n");
	sampleFunc07();
	printf("\n\n");

	getchar();
}


