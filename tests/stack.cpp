#include <catch.hpp>

#include "stack.hpp"


SCENARIO("init", "[init]"){
	stack<int> st;
	REQUIRE(st.count() == 0);
}

SCENARIO("push", "[push]")  {
	stack<int> st;
	st.push(1);
	st.push(2);
	REQUIRE(st.count() == 2);
}

SCENARIO("pop", "[pop]"){
	stack<int> st;
	st.push(1);
	st.push(2);
	st.pop();
	REQUIRE(st.count() == 1 );
}

/*SCENARIO("top", "[top]") {
	 stack<int>st;
    	st.push(1);
	REQUIRE(st.top() == 1);
}*/

SCENARIO("operator=", "[operator]") {
	stack<int> st1;
	st1.push(1);
	st1.push(2);
	st1.push(3);
	stack<int> st2 = st1;
	REQUIRE(st1.count() == st2.count());

}

/*SCENARIO("empty", "[empty]") {
	stack<int> st;
	st.empty();
	REQUIRE(st.empty() == 1);
}*/
