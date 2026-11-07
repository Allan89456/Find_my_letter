#include "CUnit/Basic.h"
#include "../src/lib/keyboard.h"
#include "../src/lib/keyboard.c"

void dummy_test(){
    CU_ASSERT_EQUAL(1,1);
}

void compare_choice_test(){
	char firstParam[] ={'a', 'A', 'b', 'B', '7', '*', '1', '0'};
	char secondParam ='A';
	unsigned short expected[] ={2, 2, 3, 3, 0, 0, 1, 4};
	char nbOfTests = sizeof(expected) / sizeof(int);

	for(int i = 0; i < nbOfTests; i++){
		int result = compare_choice(firstParam[i], secondParam);
		CU_ASSERT_EQUAL(result, expected[i]);
		if(result != expected[i]){
			printf("\n[test %d] ", i + 1);
			printf("compare_choice(%d, %d)", firstParam[i], secondParam);
			printf("\treturn : %d,\texpected : %d\t", result, expected[i]);
		}
	}
}

void is_game_over_test(){
	unsigned short firstParam[] ={3,4,3,4};
	unsigned short secondParam[] ={1,1,0,0};
	char expected[] ={1,0,0,0};
	int nbOfTests = sizeof(expected) / sizeof(int);

	for(int i = 0; i < nbOfTests; i++){
		char result = is_game_over(firstParam[i], secondParam[i]);
		CU_ASSERT_EQUAL(result, expected[i]);
		if(result != expected[i]){
			printf("\n[test %d] ", i + 1);
			printf("is_game_over(%d, %d)", firstParam[i], secondParam[i]);
			printf("\treturn : %d,\texpected : %d\t", result, expected[i]);
		}
	}
}

int main(void){
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("is_game_over_test_suite", 0, 0);
    if ( pSuite == NULL ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "dummy_test", dummy_test)
    	|| NULL == CU_add_test(pSuite, "compare_choice_test", compare_choice_test)
    	|| NULL == CU_add_test(pSuite, "is_game_over_test", is_game_over_test)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    return CU_get_error();
}