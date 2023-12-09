#include "test_date.h"

void test_date() {
	std::cout << "Testing is_date()..." << '\n'
	          << '\n';

	test_is_valid_date(2020, Month::feb, 29);
	test_is_valid_date(2019, Month::feb, 29, true);

	std::cout << '\n'
	          << "Testing is_leap_year()..." << '\n'
	          << '\n';

	test_leap_year_helper(2020);
	test_leap_year_helper(2019, true);
	test_leap_year_helper(400 * 5);
	test_leap_year_helper(400 * 5 + 100, true);

	std::cout << '\n'
	          << "Testing add_years()..." << '\n'
	          << '\n';

	test_add_year_eof_feb();

	test_add_days_multiple();

	std::cout << '\n'
	          << "Testing add_months()..." << '\n'
	          << '\n';

	test_add_months_multiple();

	std::cout << '\n'
	          << "Testing days_from_sofm_until_eofy()..." << '\n'
	          << '\n';

	test_days_until_eofy_multiple();

	std::cout << '\n'
	          << "Testing days_from_sofy_until_sofm()..." << '\n'
	          << '\n';

	test_days_until_sofm_multiple();

	std::cout << '\n'
	          << "Testing leap_years_from_year_span()..." << '\n'
	          << '\n';

	test_count_leap_years_multiple();

	std::cout << '\n'
	          << "Testing duration_in_days()..." << '\n'
	          << '\n';

	test_duration_multiple();

	std::cout << '\n'
	          << "Testing day_of_the_week()..." << '\n'
	          << '\n';

	test_dotw_multiple();

	std::cout << '\n'
	          << "Testing weeks_per_year()..." << '\n'
	          << '\n';

	test_wpyear_multiple();

	std::cout << '\n'
	          << "Testing next_workday()..." << '\n'
	          << '\n';

	test_workday_multiple();

	std::cout << '\n'
	          << "Testing week_of_year()..." << '\n'
	          << '\n';

	test_wofyear_multiple();
}
