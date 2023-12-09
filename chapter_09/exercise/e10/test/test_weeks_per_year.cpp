#include "test_date.h"
#include <string>

void test_wpyear(int year, int expected) {
	int weeks{ weeks_per_year(year) };
	if (weeks != expected) {
		throw std::runtime_error(
			"Wrong number of weeks for year: " +
			std::to_string(year) +
			". Expected: " + std::to_string(expected) +
			" but got " + std::to_string(weeks)
		);
	}
}

void test_wpyear_multiple() {
	// Silly amount of testing since the only source for the "method"
	// used to determine the number of weeks was so "vague" in its formulation
	// I was not sure it would work.
	std::cout << "Testing years 1601 to 3000..." << '\n';
	test_wpyear(1601, 52);
	test_wpyear(1602, 52);
	test_wpyear(1603, 52);
	test_wpyear(1604, 53);
	test_wpyear(1605, 52);
	test_wpyear(1606, 52);
	test_wpyear(1607, 52);
	test_wpyear(1608, 52);
	test_wpyear(1609, 53);
	test_wpyear(1610, 52);
	test_wpyear(1611, 52);
	test_wpyear(1612, 52);
	test_wpyear(1613, 52);
	test_wpyear(1614, 52);
	test_wpyear(1615, 53);
	test_wpyear(1616, 52);
	test_wpyear(1617, 52);
	test_wpyear(1618, 52);
	test_wpyear(1619, 52);
	test_wpyear(1620, 53);
	test_wpyear(1621, 52);
	test_wpyear(1622, 52);
	test_wpyear(1623, 52);
	test_wpyear(1624, 52);
	test_wpyear(1625, 52);
	test_wpyear(1626, 53);
	test_wpyear(1627, 52);
	test_wpyear(1628, 52);
	test_wpyear(1629, 52);
	test_wpyear(1630, 52);
	test_wpyear(1631, 52);
	test_wpyear(1632, 53);
	test_wpyear(1633, 52);
	test_wpyear(1634, 52);
	test_wpyear(1635, 52);
	test_wpyear(1636, 52);
	test_wpyear(1637, 53);
	test_wpyear(1638, 52);
	test_wpyear(1639, 52);
	test_wpyear(1640, 52);
	test_wpyear(1641, 52);
	test_wpyear(1642, 52);
	test_wpyear(1643, 53);
	test_wpyear(1644, 52);
	test_wpyear(1645, 52);
	test_wpyear(1646, 52);
	test_wpyear(1647, 52);
	test_wpyear(1648, 53);
	test_wpyear(1649, 52);
	test_wpyear(1650, 52);
	test_wpyear(1651, 52);
	test_wpyear(1652, 52);
	test_wpyear(1653, 52);
	test_wpyear(1654, 53);
	test_wpyear(1655, 52);
	test_wpyear(1656, 52);
	test_wpyear(1657, 52);
	test_wpyear(1658, 52);
	test_wpyear(1659, 52);
	test_wpyear(1660, 53);
	test_wpyear(1661, 52);
	test_wpyear(1662, 52);
	test_wpyear(1663, 52);
	test_wpyear(1664, 52);
	test_wpyear(1665, 53);
	test_wpyear(1666, 52);
	test_wpyear(1667, 52);
	test_wpyear(1668, 52);
	test_wpyear(1669, 52);
	test_wpyear(1670, 52);
	test_wpyear(1671, 53);
	test_wpyear(1672, 52);
	test_wpyear(1673, 52);
	test_wpyear(1674, 52);
	test_wpyear(1675, 52);
	test_wpyear(1676, 53);
	test_wpyear(1677, 52);
	test_wpyear(1678, 52);
	test_wpyear(1679, 52);
	test_wpyear(1680, 52);
	test_wpyear(1681, 52);
	test_wpyear(1682, 53);
	test_wpyear(1683, 52);
	test_wpyear(1684, 52);
	test_wpyear(1685, 52);
	test_wpyear(1686, 52);
	test_wpyear(1687, 52);
	test_wpyear(1688, 53);
	test_wpyear(1689, 52);
	test_wpyear(1690, 52);
	test_wpyear(1691, 52);
	test_wpyear(1692, 52);
	test_wpyear(1693, 53);
	test_wpyear(1694, 52);
	test_wpyear(1695, 52);
	test_wpyear(1696, 52);
	test_wpyear(1697, 52);
	test_wpyear(1698, 52);
	test_wpyear(1699, 53);
	test_wpyear(1700, 52);
	std::cout << "Years 1601 to 1700 cleared...";
	std::cout << ' ';
	test_wpyear(1701, 52);
	test_wpyear(1702, 52);
	test_wpyear(1703, 52);
	test_wpyear(1704, 52);
	test_wpyear(1705, 53);
	test_wpyear(1706, 52);
	test_wpyear(1707, 52);
	test_wpyear(1708, 52);
	test_wpyear(1709, 52);
	test_wpyear(1710, 52);
	test_wpyear(1711, 53);
	test_wpyear(1712, 52);
	test_wpyear(1713, 52);
	test_wpyear(1714, 52);
	test_wpyear(1715, 52);
	test_wpyear(1716, 53);
	test_wpyear(1717, 52);
	test_wpyear(1718, 52);
	test_wpyear(1719, 52);
	test_wpyear(1720, 52);
	test_wpyear(1721, 52);
	test_wpyear(1722, 53);
	test_wpyear(1723, 52);
	test_wpyear(1724, 52);
	test_wpyear(1725, 52);
	test_wpyear(1726, 52);
	test_wpyear(1727, 52);
	test_wpyear(1728, 53);
	test_wpyear(1729, 52);
	test_wpyear(1730, 52);
	test_wpyear(1731, 52);
	test_wpyear(1732, 52);
	test_wpyear(1733, 53);
	test_wpyear(1734, 52);
	test_wpyear(1735, 52);
	test_wpyear(1736, 52);
	test_wpyear(1737, 52);
	test_wpyear(1738, 52);
	test_wpyear(1739, 53);
	test_wpyear(1740, 52);
	test_wpyear(1741, 52);
	test_wpyear(1742, 52);
	test_wpyear(1743, 52);
	test_wpyear(1744, 53);
	test_wpyear(1745, 52);
	test_wpyear(1746, 52);
	test_wpyear(1747, 52);
	test_wpyear(1748, 52);
	test_wpyear(1749, 52);
	test_wpyear(1750, 53);
	test_wpyear(1751, 52);
	test_wpyear(1752, 52);
	test_wpyear(1753, 52);
	test_wpyear(1754, 52);
	test_wpyear(1755, 52);
	test_wpyear(1756, 53);
	test_wpyear(1757, 52);
	test_wpyear(1758, 52);
	test_wpyear(1759, 52);
	test_wpyear(1760, 52);
	test_wpyear(1761, 53);
	test_wpyear(1762, 52);
	test_wpyear(1763, 52);
	test_wpyear(1764, 52);
	test_wpyear(1765, 52);
	test_wpyear(1766, 52);
	test_wpyear(1767, 53);
	test_wpyear(1768, 52);
	test_wpyear(1769, 52);
	test_wpyear(1770, 52);
	test_wpyear(1771, 52);
	test_wpyear(1772, 53);
	test_wpyear(1773, 52);
	test_wpyear(1774, 52);
	test_wpyear(1775, 52);
	test_wpyear(1776, 52);
	test_wpyear(1777, 52);
	test_wpyear(1778, 53);
	test_wpyear(1779, 52);
	test_wpyear(1780, 52);
	test_wpyear(1781, 52);
	test_wpyear(1782, 52);
	test_wpyear(1783, 52);
	test_wpyear(1784, 53);
	test_wpyear(1785, 52);
	test_wpyear(1786, 52);
	test_wpyear(1787, 52);
	test_wpyear(1788, 52);
	test_wpyear(1789, 53);
	test_wpyear(1790, 52);
	test_wpyear(1791, 52);
	test_wpyear(1792, 52);
	test_wpyear(1793, 52);
	test_wpyear(1794, 52);
	test_wpyear(1795, 53);
	test_wpyear(1796, 52);
	test_wpyear(1797, 52);
	test_wpyear(1798, 52);
	test_wpyear(1799, 52);
	test_wpyear(1800, 52);
	std::cout << "Years 1701 to 1800 cleared...";
	std::cout << '\n';
	test_wpyear(1801, 53);
	test_wpyear(1802, 52);
	test_wpyear(1803, 52);
	test_wpyear(1804, 52);
	test_wpyear(1805, 52);
	test_wpyear(1806, 52);
	test_wpyear(1807, 53);
	test_wpyear(1808, 52);
	test_wpyear(1809, 52);
	test_wpyear(1810, 52);
	test_wpyear(1811, 52);
	test_wpyear(1812, 53);
	test_wpyear(1813, 52);
	test_wpyear(1814, 52);
	test_wpyear(1815, 52);
	test_wpyear(1816, 52);
	test_wpyear(1817, 52);
	test_wpyear(1818, 53);
	test_wpyear(1819, 52);
	test_wpyear(1820, 52);
	test_wpyear(1821, 52);
	test_wpyear(1822, 52);
	test_wpyear(1823, 52);
	test_wpyear(1824, 53);
	test_wpyear(1825, 52);
	test_wpyear(1826, 52);
	test_wpyear(1827, 52);
	test_wpyear(1828, 52);
	test_wpyear(1829, 53);
	test_wpyear(1830, 52);
	test_wpyear(1831, 52);
	test_wpyear(1832, 52);
	test_wpyear(1833, 52);
	test_wpyear(1834, 52);
	test_wpyear(1835, 53);
	test_wpyear(1836, 52);
	test_wpyear(1837, 52);
	test_wpyear(1838, 52);
	test_wpyear(1839, 52);
	test_wpyear(1840, 53);
	test_wpyear(1841, 52);
	test_wpyear(1842, 52);
	test_wpyear(1843, 52);
	test_wpyear(1844, 52);
	test_wpyear(1845, 52);
	test_wpyear(1846, 53);
	test_wpyear(1847, 52);
	test_wpyear(1848, 52);
	test_wpyear(1849, 52);
	test_wpyear(1850, 52);
	test_wpyear(1851, 52);
	test_wpyear(1852, 53);
	test_wpyear(1853, 52);
	test_wpyear(1854, 52);
	test_wpyear(1855, 52);
	test_wpyear(1856, 52);
	test_wpyear(1857, 53);
	test_wpyear(1858, 52);
	test_wpyear(1859, 52);
	test_wpyear(1860, 52);
	test_wpyear(1861, 52);
	test_wpyear(1862, 52);
	test_wpyear(1863, 53);
	test_wpyear(1864, 52);
	test_wpyear(1865, 52);
	test_wpyear(1866, 52);
	test_wpyear(1867, 52);
	test_wpyear(1868, 53);
	test_wpyear(1869, 52);
	test_wpyear(1870, 52);
	test_wpyear(1871, 52);
	test_wpyear(1872, 52);
	test_wpyear(1873, 52);
	test_wpyear(1874, 53);
	test_wpyear(1875, 52);
	test_wpyear(1876, 52);
	test_wpyear(1877, 52);
	test_wpyear(1878, 52);
	test_wpyear(1879, 52);
	test_wpyear(1880, 53);
	test_wpyear(1881, 52);
	test_wpyear(1882, 52);
	test_wpyear(1883, 52);
	test_wpyear(1884, 52);
	test_wpyear(1885, 53);
	test_wpyear(1886, 52);
	test_wpyear(1887, 52);
	test_wpyear(1888, 52);
	test_wpyear(1889, 52);
	test_wpyear(1890, 52);
	test_wpyear(1891, 53);
	test_wpyear(1892, 52);
	test_wpyear(1893, 52);
	test_wpyear(1894, 52);
	test_wpyear(1895, 52);
	test_wpyear(1896, 53);
	test_wpyear(1897, 52);
	test_wpyear(1898, 52);
	test_wpyear(1899, 52);
	test_wpyear(1900, 52);
	std::cout << "Years 1801 to 1900 cleared...";
	std::cout << ' ';
	test_wpyear(1901, 52);
	test_wpyear(1902, 52);
	test_wpyear(1903, 53);
	test_wpyear(1904, 52);
	test_wpyear(1905, 52);
	test_wpyear(1906, 52);
	test_wpyear(1907, 52);
	test_wpyear(1908, 53);
	test_wpyear(1909, 52);
	test_wpyear(1910, 52);
	test_wpyear(1911, 52);
	test_wpyear(1912, 52);
	test_wpyear(1913, 52);
	test_wpyear(1914, 53);
	test_wpyear(1915, 52);
	test_wpyear(1916, 52);
	test_wpyear(1917, 52);
	test_wpyear(1918, 52);
	test_wpyear(1919, 52);
	test_wpyear(1920, 53);
	test_wpyear(1921, 52);
	test_wpyear(1922, 52);
	test_wpyear(1923, 52);
	test_wpyear(1924, 52);
	test_wpyear(1925, 53);
	test_wpyear(1926, 52);
	test_wpyear(1927, 52);
	test_wpyear(1928, 52);
	test_wpyear(1929, 52);
	test_wpyear(1930, 52);
	test_wpyear(1931, 53);
	test_wpyear(1932, 52);
	test_wpyear(1933, 52);
	test_wpyear(1934, 52);
	test_wpyear(1935, 52);
	test_wpyear(1936, 53);
	test_wpyear(1937, 52);
	test_wpyear(1938, 52);
	test_wpyear(1939, 52);
	test_wpyear(1940, 52);
	test_wpyear(1941, 52);
	test_wpyear(1942, 53);
	test_wpyear(1943, 52);
	test_wpyear(1944, 52);
	test_wpyear(1945, 52);
	test_wpyear(1946, 52);
	test_wpyear(1947, 52);
	test_wpyear(1948, 53);
	test_wpyear(1949, 52);
	test_wpyear(1950, 52);
	test_wpyear(1951, 52);
	test_wpyear(1952, 52);
	test_wpyear(1953, 53);
	test_wpyear(1954, 52);
	test_wpyear(1955, 52);
	test_wpyear(1956, 52);
	test_wpyear(1957, 52);
	test_wpyear(1958, 52);
	test_wpyear(1959, 53);
	test_wpyear(1960, 52);
	test_wpyear(1961, 52);
	test_wpyear(1962, 52);
	test_wpyear(1963, 52);
	test_wpyear(1964, 53);
	test_wpyear(1965, 52);
	test_wpyear(1966, 52);
	test_wpyear(1967, 52);
	test_wpyear(1968, 52);
	test_wpyear(1969, 52);
	test_wpyear(1970, 53);
	test_wpyear(1971, 52);
	test_wpyear(1972, 52);
	test_wpyear(1973, 52);
	test_wpyear(1974, 52);
	test_wpyear(1975, 52);
	test_wpyear(1976, 53);
	test_wpyear(1977, 52);
	test_wpyear(1978, 52);
	test_wpyear(1979, 52);
	test_wpyear(1980, 52);
	test_wpyear(1981, 53);
	test_wpyear(1982, 52);
	test_wpyear(1983, 52);
	test_wpyear(1984, 52);
	test_wpyear(1985, 52);
	test_wpyear(1986, 52);
	test_wpyear(1987, 53);
	test_wpyear(1988, 52);
	test_wpyear(1989, 52);
	test_wpyear(1990, 52);
	test_wpyear(1991, 52);
	test_wpyear(1992, 53);
	test_wpyear(1993, 52);
	test_wpyear(1994, 52);
	test_wpyear(1995, 52);
	test_wpyear(1996, 52);
	test_wpyear(1997, 52);
	test_wpyear(1998, 53);
	test_wpyear(1999, 52);
	test_wpyear(2000, 52);
	std::cout << "Years 1901 to 2000 cleared...";
	std::cout << '\n';
	test_wpyear(2001, 52);
	test_wpyear(2002, 52);
	test_wpyear(2003, 52);
	test_wpyear(2004, 53);
	test_wpyear(2005, 52);
	test_wpyear(2006, 52);
	test_wpyear(2007, 52);
	test_wpyear(2008, 52);
	test_wpyear(2009, 53);
	test_wpyear(2010, 52);
	test_wpyear(2011, 52);
	test_wpyear(2012, 52);
	test_wpyear(2013, 52);
	test_wpyear(2014, 52);
	test_wpyear(2015, 53);
	test_wpyear(2016, 52);
	test_wpyear(2017, 52);
	test_wpyear(2018, 52);
	test_wpyear(2019, 52);
	test_wpyear(2020, 53);
	test_wpyear(2021, 52);
	test_wpyear(2022, 52);
	test_wpyear(2023, 52);
	test_wpyear(2024, 52);
	test_wpyear(2025, 52);
	test_wpyear(2026, 53);
	test_wpyear(2027, 52);
	test_wpyear(2028, 52);
	test_wpyear(2029, 52);
	test_wpyear(2030, 52);
	test_wpyear(2031, 52);
	test_wpyear(2032, 53);
	test_wpyear(2033, 52);
	test_wpyear(2034, 52);
	test_wpyear(2035, 52);
	test_wpyear(2036, 52);
	test_wpyear(2037, 53);
	test_wpyear(2038, 52);
	test_wpyear(2039, 52);
	test_wpyear(2040, 52);
	test_wpyear(2041, 52);
	test_wpyear(2042, 52);
	test_wpyear(2043, 53);
	test_wpyear(2044, 52);
	test_wpyear(2045, 52);
	test_wpyear(2046, 52);
	test_wpyear(2047, 52);
	test_wpyear(2048, 53);
	test_wpyear(2049, 52);
	test_wpyear(2050, 52);
	test_wpyear(2051, 52);
	test_wpyear(2052, 52);
	test_wpyear(2053, 52);
	test_wpyear(2054, 53);
	test_wpyear(2055, 52);
	test_wpyear(2056, 52);
	test_wpyear(2057, 52);
	test_wpyear(2058, 52);
	test_wpyear(2059, 52);
	test_wpyear(2060, 53);
	test_wpyear(2061, 52);
	test_wpyear(2062, 52);
	test_wpyear(2063, 52);
	test_wpyear(2064, 52);
	test_wpyear(2065, 53);
	test_wpyear(2066, 52);
	test_wpyear(2067, 52);
	test_wpyear(2068, 52);
	test_wpyear(2069, 52);
	test_wpyear(2070, 52);
	test_wpyear(2071, 53);
	test_wpyear(2072, 52);
	test_wpyear(2073, 52);
	test_wpyear(2074, 52);
	test_wpyear(2075, 52);
	test_wpyear(2076, 53);
	test_wpyear(2077, 52);
	test_wpyear(2078, 52);
	test_wpyear(2079, 52);
	test_wpyear(2080, 52);
	test_wpyear(2081, 52);
	test_wpyear(2082, 53);
	test_wpyear(2083, 52);
	test_wpyear(2084, 52);
	test_wpyear(2085, 52);
	test_wpyear(2086, 52);
	test_wpyear(2087, 52);
	test_wpyear(2088, 53);
	test_wpyear(2089, 52);
	test_wpyear(2090, 52);
	test_wpyear(2091, 52);
	test_wpyear(2092, 52);
	test_wpyear(2093, 53);
	test_wpyear(2094, 52);
	test_wpyear(2095, 52);
	test_wpyear(2096, 52);
	test_wpyear(2097, 52);
	test_wpyear(2098, 52);
	test_wpyear(2099, 53);
	test_wpyear(2100, 52);
	std::cout << "Years 2001 to 2100 cleared...";
	std::cout << ' ';
	test_wpyear(2101, 52);
	test_wpyear(2102, 52);
	test_wpyear(2103, 52);
	test_wpyear(2104, 52);
	test_wpyear(2105, 53);
	test_wpyear(2106, 52);
	test_wpyear(2107, 52);
	test_wpyear(2108, 52);
	test_wpyear(2109, 52);
	test_wpyear(2110, 52);
	test_wpyear(2111, 53);
	test_wpyear(2112, 52);
	test_wpyear(2113, 52);
	test_wpyear(2114, 52);
	test_wpyear(2115, 52);
	test_wpyear(2116, 53);
	test_wpyear(2117, 52);
	test_wpyear(2118, 52);
	test_wpyear(2119, 52);
	test_wpyear(2120, 52);
	test_wpyear(2121, 52);
	test_wpyear(2122, 53);
	test_wpyear(2123, 52);
	test_wpyear(2124, 52);
	test_wpyear(2125, 52);
	test_wpyear(2126, 52);
	test_wpyear(2127, 52);
	test_wpyear(2128, 53);
	test_wpyear(2129, 52);
	test_wpyear(2130, 52);
	test_wpyear(2131, 52);
	test_wpyear(2132, 52);
	test_wpyear(2133, 53);
	test_wpyear(2134, 52);
	test_wpyear(2135, 52);
	test_wpyear(2136, 52);
	test_wpyear(2137, 52);
	test_wpyear(2138, 52);
	test_wpyear(2139, 53);
	test_wpyear(2140, 52);
	test_wpyear(2141, 52);
	test_wpyear(2142, 52);
	test_wpyear(2143, 52);
	test_wpyear(2144, 53);
	test_wpyear(2145, 52);
	test_wpyear(2146, 52);
	test_wpyear(2147, 52);
	test_wpyear(2148, 52);
	test_wpyear(2149, 52);
	test_wpyear(2150, 53);
	test_wpyear(2151, 52);
	test_wpyear(2152, 52);
	test_wpyear(2153, 52);
	test_wpyear(2154, 52);
	test_wpyear(2155, 52);
	test_wpyear(2156, 53);
	test_wpyear(2157, 52);
	test_wpyear(2158, 52);
	test_wpyear(2159, 52);
	test_wpyear(2160, 52);
	test_wpyear(2161, 53);
	test_wpyear(2162, 52);
	test_wpyear(2163, 52);
	test_wpyear(2164, 52);
	test_wpyear(2165, 52);
	test_wpyear(2166, 52);
	test_wpyear(2167, 53);
	test_wpyear(2168, 52);
	test_wpyear(2169, 52);
	test_wpyear(2170, 52);
	test_wpyear(2171, 52);
	test_wpyear(2172, 53);
	test_wpyear(2173, 52);
	test_wpyear(2174, 52);
	test_wpyear(2175, 52);
	test_wpyear(2176, 52);
	test_wpyear(2177, 52);
	test_wpyear(2178, 53);
	test_wpyear(2179, 52);
	test_wpyear(2180, 52);
	test_wpyear(2181, 52);
	test_wpyear(2182, 52);
	test_wpyear(2183, 52);
	test_wpyear(2184, 53);
	test_wpyear(2185, 52);
	test_wpyear(2186, 52);
	test_wpyear(2187, 52);
	test_wpyear(2188, 52);
	test_wpyear(2189, 53);
	test_wpyear(2190, 52);
	test_wpyear(2191, 52);
	test_wpyear(2192, 52);
	test_wpyear(2193, 52);
	test_wpyear(2194, 52);
	test_wpyear(2195, 53);
	test_wpyear(2196, 52);
	test_wpyear(2197, 52);
	test_wpyear(2198, 52);
	test_wpyear(2199, 52);
	test_wpyear(2200, 52);
	std::cout << "Years 2101 to 2200 cleared...";
	std::cout << '\n';
	test_wpyear(2201, 53);
	test_wpyear(2202, 52);
	test_wpyear(2203, 52);
	test_wpyear(2204, 52);
	test_wpyear(2205, 52);
	test_wpyear(2206, 52);
	test_wpyear(2207, 53);
	test_wpyear(2208, 52);
	test_wpyear(2209, 52);
	test_wpyear(2210, 52);
	test_wpyear(2211, 52);
	test_wpyear(2212, 53);
	test_wpyear(2213, 52);
	test_wpyear(2214, 52);
	test_wpyear(2215, 52);
	test_wpyear(2216, 52);
	test_wpyear(2217, 52);
	test_wpyear(2218, 53);
	test_wpyear(2219, 52);
	test_wpyear(2220, 52);
	test_wpyear(2221, 52);
	test_wpyear(2222, 52);
	test_wpyear(2223, 52);
	test_wpyear(2224, 53);
	test_wpyear(2225, 52);
	test_wpyear(2226, 52);
	test_wpyear(2227, 52);
	test_wpyear(2228, 52);
	test_wpyear(2229, 53);
	test_wpyear(2230, 52);
	test_wpyear(2231, 52);
	test_wpyear(2232, 52);
	test_wpyear(2233, 52);
	test_wpyear(2234, 52);
	test_wpyear(2235, 53);
	test_wpyear(2236, 52);
	test_wpyear(2237, 52);
	test_wpyear(2238, 52);
	test_wpyear(2239, 52);
	test_wpyear(2240, 53);
	test_wpyear(2241, 52);
	test_wpyear(2242, 52);
	test_wpyear(2243, 52);
	test_wpyear(2244, 52);
	test_wpyear(2245, 52);
	test_wpyear(2246, 53);
	test_wpyear(2247, 52);
	test_wpyear(2248, 52);
	test_wpyear(2249, 52);
	test_wpyear(2250, 52);
	test_wpyear(2251, 52);
	test_wpyear(2252, 53);
	test_wpyear(2253, 52);
	test_wpyear(2254, 52);
	test_wpyear(2255, 52);
	test_wpyear(2256, 52);
	test_wpyear(2257, 53);
	test_wpyear(2258, 52);
	test_wpyear(2259, 52);
	test_wpyear(2260, 52);
	test_wpyear(2261, 52);
	test_wpyear(2262, 52);
	test_wpyear(2263, 53);
	test_wpyear(2264, 52);
	test_wpyear(2265, 52);
	test_wpyear(2266, 52);
	test_wpyear(2267, 52);
	test_wpyear(2268, 53);
	test_wpyear(2269, 52);
	test_wpyear(2270, 52);
	test_wpyear(2271, 52);
	test_wpyear(2272, 52);
	test_wpyear(2273, 52);
	test_wpyear(2274, 53);
	test_wpyear(2275, 52);
	test_wpyear(2276, 52);
	test_wpyear(2277, 52);
	test_wpyear(2278, 52);
	test_wpyear(2279, 52);
	test_wpyear(2280, 53);
	test_wpyear(2281, 52);
	test_wpyear(2282, 52);
	test_wpyear(2283, 52);
	test_wpyear(2284, 52);
	test_wpyear(2285, 53);
	test_wpyear(2286, 52);
	test_wpyear(2287, 52);
	test_wpyear(2288, 52);
	test_wpyear(2289, 52);
	test_wpyear(2290, 52);
	test_wpyear(2291, 53);
	test_wpyear(2292, 52);
	test_wpyear(2293, 52);
	test_wpyear(2294, 52);
	test_wpyear(2295, 52);
	test_wpyear(2296, 53);
	test_wpyear(2297, 52);
	test_wpyear(2298, 52);
	test_wpyear(2299, 52);
	test_wpyear(2300, 52);
	std::cout << "Years 2201 to 2300 cleared...";
	std::cout << ' ';
	test_wpyear(2301, 52);
	test_wpyear(2302, 52);
	test_wpyear(2303, 53);
	test_wpyear(2304, 52);
	test_wpyear(2305, 52);
	test_wpyear(2306, 52);
	test_wpyear(2307, 52);
	test_wpyear(2308, 53);
	test_wpyear(2309, 52);
	test_wpyear(2310, 52);
	test_wpyear(2311, 52);
	test_wpyear(2312, 52);
	test_wpyear(2313, 52);
	test_wpyear(2314, 53);
	test_wpyear(2315, 52);
	test_wpyear(2316, 52);
	test_wpyear(2317, 52);
	test_wpyear(2318, 52);
	test_wpyear(2319, 52);
	test_wpyear(2320, 53);
	test_wpyear(2321, 52);
	test_wpyear(2322, 52);
	test_wpyear(2323, 52);
	test_wpyear(2324, 52);
	test_wpyear(2325, 53);
	test_wpyear(2326, 52);
	test_wpyear(2327, 52);
	test_wpyear(2328, 52);
	test_wpyear(2329, 52);
	test_wpyear(2330, 52);
	test_wpyear(2331, 53);
	test_wpyear(2332, 52);
	test_wpyear(2333, 52);
	test_wpyear(2334, 52);
	test_wpyear(2335, 52);
	test_wpyear(2336, 53);
	test_wpyear(2337, 52);
	test_wpyear(2338, 52);
	test_wpyear(2339, 52);
	test_wpyear(2340, 52);
	test_wpyear(2341, 52);
	test_wpyear(2342, 53);
	test_wpyear(2343, 52);
	test_wpyear(2344, 52);
	test_wpyear(2345, 52);
	test_wpyear(2346, 52);
	test_wpyear(2347, 52);
	test_wpyear(2348, 53);
	test_wpyear(2349, 52);
	test_wpyear(2350, 52);
	test_wpyear(2351, 52);
	test_wpyear(2352, 52);
	test_wpyear(2353, 53);
	test_wpyear(2354, 52);
	test_wpyear(2355, 52);
	test_wpyear(2356, 52);
	test_wpyear(2357, 52);
	test_wpyear(2358, 52);
	test_wpyear(2359, 53);
	test_wpyear(2360, 52);
	test_wpyear(2361, 52);
	test_wpyear(2362, 52);
	test_wpyear(2363, 52);
	test_wpyear(2364, 53);
	test_wpyear(2365, 52);
	test_wpyear(2366, 52);
	test_wpyear(2367, 52);
	test_wpyear(2368, 52);
	test_wpyear(2369, 52);
	test_wpyear(2370, 53);
	test_wpyear(2371, 52);
	test_wpyear(2372, 52);
	test_wpyear(2373, 52);
	test_wpyear(2374, 52);
	test_wpyear(2375, 52);
	test_wpyear(2376, 53);
	test_wpyear(2377, 52);
	test_wpyear(2378, 52);
	test_wpyear(2379, 52);
	test_wpyear(2380, 52);
	test_wpyear(2381, 53);
	test_wpyear(2382, 52);
	test_wpyear(2383, 52);
	test_wpyear(2384, 52);
	test_wpyear(2385, 52);
	test_wpyear(2386, 52);
	test_wpyear(2387, 53);
	test_wpyear(2388, 52);
	test_wpyear(2389, 52);
	test_wpyear(2390, 52);
	test_wpyear(2391, 52);
	test_wpyear(2392, 53);
	test_wpyear(2393, 52);
	test_wpyear(2394, 52);
	test_wpyear(2395, 52);
	test_wpyear(2396, 52);
	test_wpyear(2397, 52);
	test_wpyear(2398, 53);
	test_wpyear(2399, 52);
	test_wpyear(2400, 52);
	std::cout << "Years 2301 to 2400 cleared...";
	std::cout << '\n';
	test_wpyear(2401, 52);
	test_wpyear(2402, 52);
	test_wpyear(2403, 52);
	test_wpyear(2404, 53);
	test_wpyear(2405, 52);
	test_wpyear(2406, 52);
	test_wpyear(2407, 52);
	test_wpyear(2408, 52);
	test_wpyear(2409, 53);
	test_wpyear(2410, 52);
	test_wpyear(2411, 52);
	test_wpyear(2412, 52);
	test_wpyear(2413, 52);
	test_wpyear(2414, 52);
	test_wpyear(2415, 53);
	test_wpyear(2416, 52);
	test_wpyear(2417, 52);
	test_wpyear(2418, 52);
	test_wpyear(2419, 52);
	test_wpyear(2420, 53);
	test_wpyear(2421, 52);
	test_wpyear(2422, 52);
	test_wpyear(2423, 52);
	test_wpyear(2424, 52);
	test_wpyear(2425, 52);
	test_wpyear(2426, 53);
	test_wpyear(2427, 52);
	test_wpyear(2428, 52);
	test_wpyear(2429, 52);
	test_wpyear(2430, 52);
	test_wpyear(2431, 52);
	test_wpyear(2432, 53);
	test_wpyear(2433, 52);
	test_wpyear(2434, 52);
	test_wpyear(2435, 52);
	test_wpyear(2436, 52);
	test_wpyear(2437, 53);
	test_wpyear(2438, 52);
	test_wpyear(2439, 52);
	test_wpyear(2440, 52);
	test_wpyear(2441, 52);
	test_wpyear(2442, 52);
	test_wpyear(2443, 53);
	test_wpyear(2444, 52);
	test_wpyear(2445, 52);
	test_wpyear(2446, 52);
	test_wpyear(2447, 52);
	test_wpyear(2448, 53);
	test_wpyear(2449, 52);
	test_wpyear(2450, 52);
	test_wpyear(2451, 52);
	test_wpyear(2452, 52);
	test_wpyear(2453, 52);
	test_wpyear(2454, 53);
	test_wpyear(2455, 52);
	test_wpyear(2456, 52);
	test_wpyear(2457, 52);
	test_wpyear(2458, 52);
	test_wpyear(2459, 52);
	test_wpyear(2460, 53);
	test_wpyear(2461, 52);
	test_wpyear(2462, 52);
	test_wpyear(2463, 52);
	test_wpyear(2464, 52);
	test_wpyear(2465, 53);
	test_wpyear(2466, 52);
	test_wpyear(2467, 52);
	test_wpyear(2468, 52);
	test_wpyear(2469, 52);
	test_wpyear(2470, 52);
	test_wpyear(2471, 53);
	test_wpyear(2472, 52);
	test_wpyear(2473, 52);
	test_wpyear(2474, 52);
	test_wpyear(2475, 52);
	test_wpyear(2476, 53);
	test_wpyear(2477, 52);
	test_wpyear(2478, 52);
	test_wpyear(2479, 52);
	test_wpyear(2480, 52);
	test_wpyear(2481, 52);
	test_wpyear(2482, 53);
	test_wpyear(2483, 52);
	test_wpyear(2484, 52);
	test_wpyear(2485, 52);
	test_wpyear(2486, 52);
	test_wpyear(2487, 52);
	test_wpyear(2488, 53);
	test_wpyear(2489, 52);
	test_wpyear(2490, 52);
	test_wpyear(2491, 52);
	test_wpyear(2492, 52);
	test_wpyear(2493, 53);
	test_wpyear(2494, 52);
	test_wpyear(2495, 52);
	test_wpyear(2496, 52);
	test_wpyear(2497, 52);
	test_wpyear(2498, 52);
	test_wpyear(2499, 53);
	test_wpyear(2500, 52);
	std::cout << "Years 2401 to 2500 cleared...";
	std::cout << ' ';
	test_wpyear(2501, 52);
	test_wpyear(2502, 52);
	test_wpyear(2503, 52);
	test_wpyear(2504, 52);
	test_wpyear(2505, 53);
	test_wpyear(2506, 52);
	test_wpyear(2507, 52);
	test_wpyear(2508, 52);
	test_wpyear(2509, 52);
	test_wpyear(2510, 52);
	test_wpyear(2511, 53);
	test_wpyear(2512, 52);
	test_wpyear(2513, 52);
	test_wpyear(2514, 52);
	test_wpyear(2515, 52);
	test_wpyear(2516, 53);
	test_wpyear(2517, 52);
	test_wpyear(2518, 52);
	test_wpyear(2519, 52);
	test_wpyear(2520, 52);
	test_wpyear(2521, 52);
	test_wpyear(2522, 53);
	test_wpyear(2523, 52);
	test_wpyear(2524, 52);
	test_wpyear(2525, 52);
	test_wpyear(2526, 52);
	test_wpyear(2527, 52);
	test_wpyear(2528, 53);
	test_wpyear(2529, 52);
	test_wpyear(2530, 52);
	test_wpyear(2531, 52);
	test_wpyear(2532, 52);
	test_wpyear(2533, 53);
	test_wpyear(2534, 52);
	test_wpyear(2535, 52);
	test_wpyear(2536, 52);
	test_wpyear(2537, 52);
	test_wpyear(2538, 52);
	test_wpyear(2539, 53);
	test_wpyear(2540, 52);
	test_wpyear(2541, 52);
	test_wpyear(2542, 52);
	test_wpyear(2543, 52);
	test_wpyear(2544, 53);
	test_wpyear(2545, 52);
	test_wpyear(2546, 52);
	test_wpyear(2547, 52);
	test_wpyear(2548, 52);
	test_wpyear(2549, 52);
	test_wpyear(2550, 53);
	test_wpyear(2551, 52);
	test_wpyear(2552, 52);
	test_wpyear(2553, 52);
	test_wpyear(2554, 52);
	test_wpyear(2555, 52);
	test_wpyear(2556, 53);
	test_wpyear(2557, 52);
	test_wpyear(2558, 52);
	test_wpyear(2559, 52);
	test_wpyear(2560, 52);
	test_wpyear(2561, 53);
	test_wpyear(2562, 52);
	test_wpyear(2563, 52);
	test_wpyear(2564, 52);
	test_wpyear(2565, 52);
	test_wpyear(2566, 52);
	test_wpyear(2567, 53);
	test_wpyear(2568, 52);
	test_wpyear(2569, 52);
	test_wpyear(2570, 52);
	test_wpyear(2571, 52);
	test_wpyear(2572, 53);
	test_wpyear(2573, 52);
	test_wpyear(2574, 52);
	test_wpyear(2575, 52);
	test_wpyear(2576, 52);
	test_wpyear(2577, 52);
	test_wpyear(2578, 53);
	test_wpyear(2579, 52);
	test_wpyear(2580, 52);
	test_wpyear(2581, 52);
	test_wpyear(2582, 52);
	test_wpyear(2583, 52);
	test_wpyear(2584, 53);
	test_wpyear(2585, 52);
	test_wpyear(2586, 52);
	test_wpyear(2587, 52);
	test_wpyear(2588, 52);
	test_wpyear(2589, 53);
	test_wpyear(2590, 52);
	test_wpyear(2591, 52);
	test_wpyear(2592, 52);
	test_wpyear(2593, 52);
	test_wpyear(2594, 52);
	test_wpyear(2595, 53);
	test_wpyear(2596, 52);
	test_wpyear(2597, 52);
	test_wpyear(2598, 52);
	test_wpyear(2599, 52);
	test_wpyear(2600, 52);
	std::cout << "Years 2501 to 2600 cleared...";
	std::cout << '\n';
	test_wpyear(2601, 53);
	test_wpyear(2602, 52);
	test_wpyear(2603, 52);
	test_wpyear(2604, 52);
	test_wpyear(2605, 52);
	test_wpyear(2606, 52);
	test_wpyear(2607, 53);
	test_wpyear(2608, 52);
	test_wpyear(2609, 52);
	test_wpyear(2610, 52);
	test_wpyear(2611, 52);
	test_wpyear(2612, 53);
	test_wpyear(2613, 52);
	test_wpyear(2614, 52);
	test_wpyear(2615, 52);
	test_wpyear(2616, 52);
	test_wpyear(2617, 52);
	test_wpyear(2618, 53);
	test_wpyear(2619, 52);
	test_wpyear(2620, 52);
	test_wpyear(2621, 52);
	test_wpyear(2622, 52);
	test_wpyear(2623, 52);
	test_wpyear(2624, 53);
	test_wpyear(2625, 52);
	test_wpyear(2626, 52);
	test_wpyear(2627, 52);
	test_wpyear(2628, 52);
	test_wpyear(2629, 53);
	test_wpyear(2630, 52);
	test_wpyear(2631, 52);
	test_wpyear(2632, 52);
	test_wpyear(2633, 52);
	test_wpyear(2634, 52);
	test_wpyear(2635, 53);
	test_wpyear(2636, 52);
	test_wpyear(2637, 52);
	test_wpyear(2638, 52);
	test_wpyear(2639, 52);
	test_wpyear(2640, 53);
	test_wpyear(2641, 52);
	test_wpyear(2642, 52);
	test_wpyear(2643, 52);
	test_wpyear(2644, 52);
	test_wpyear(2645, 52);
	test_wpyear(2646, 53);
	test_wpyear(2647, 52);
	test_wpyear(2648, 52);
	test_wpyear(2649, 52);
	test_wpyear(2650, 52);
	test_wpyear(2651, 52);
	test_wpyear(2652, 53);
	test_wpyear(2653, 52);
	test_wpyear(2654, 52);
	test_wpyear(2655, 52);
	test_wpyear(2656, 52);
	test_wpyear(2657, 53);
	test_wpyear(2658, 52);
	test_wpyear(2659, 52);
	test_wpyear(2660, 52);
	test_wpyear(2661, 52);
	test_wpyear(2662, 52);
	test_wpyear(2663, 53);
	test_wpyear(2664, 52);
	test_wpyear(2665, 52);
	test_wpyear(2666, 52);
	test_wpyear(2667, 52);
	test_wpyear(2668, 53);
	test_wpyear(2669, 52);
	test_wpyear(2670, 52);
	test_wpyear(2671, 52);
	test_wpyear(2672, 52);
	test_wpyear(2673, 52);
	test_wpyear(2674, 53);
	test_wpyear(2675, 52);
	test_wpyear(2676, 52);
	test_wpyear(2677, 52);
	test_wpyear(2678, 52);
	test_wpyear(2679, 52);
	test_wpyear(2680, 53);
	test_wpyear(2681, 52);
	test_wpyear(2682, 52);
	test_wpyear(2683, 52);
	test_wpyear(2684, 52);
	test_wpyear(2685, 53);
	test_wpyear(2686, 52);
	test_wpyear(2687, 52);
	test_wpyear(2688, 52);
	test_wpyear(2689, 52);
	test_wpyear(2690, 52);
	test_wpyear(2691, 53);
	test_wpyear(2692, 52);
	test_wpyear(2693, 52);
	test_wpyear(2694, 52);
	test_wpyear(2695, 52);
	test_wpyear(2696, 53);
	test_wpyear(2697, 52);
	test_wpyear(2698, 52);
	test_wpyear(2699, 52);
	test_wpyear(2700, 52);
	std::cout << "Years 2601 to 2700 cleared...";
	std::cout << ' ';
	test_wpyear(2701, 52);
	test_wpyear(2702, 52);
	test_wpyear(2703, 53);
	test_wpyear(2704, 52);
	test_wpyear(2705, 52);
	test_wpyear(2706, 52);
	test_wpyear(2707, 52);
	test_wpyear(2708, 53);
	test_wpyear(2709, 52);
	test_wpyear(2710, 52);
	test_wpyear(2711, 52);
	test_wpyear(2712, 52);
	test_wpyear(2713, 52);
	test_wpyear(2714, 53);
	test_wpyear(2715, 52);
	test_wpyear(2716, 52);
	test_wpyear(2717, 52);
	test_wpyear(2718, 52);
	test_wpyear(2719, 52);
	test_wpyear(2720, 53);
	test_wpyear(2721, 52);
	test_wpyear(2722, 52);
	test_wpyear(2723, 52);
	test_wpyear(2724, 52);
	test_wpyear(2725, 53);
	test_wpyear(2726, 52);
	test_wpyear(2727, 52);
	test_wpyear(2728, 52);
	test_wpyear(2729, 52);
	test_wpyear(2730, 52);
	test_wpyear(2731, 53);
	test_wpyear(2732, 52);
	test_wpyear(2733, 52);
	test_wpyear(2734, 52);
	test_wpyear(2735, 52);
	test_wpyear(2736, 53);
	test_wpyear(2737, 52);
	test_wpyear(2738, 52);
	test_wpyear(2739, 52);
	test_wpyear(2740, 52);
	test_wpyear(2741, 52);
	test_wpyear(2742, 53);
	test_wpyear(2743, 52);
	test_wpyear(2744, 52);
	test_wpyear(2745, 52);
	test_wpyear(2746, 52);
	test_wpyear(2747, 52);
	test_wpyear(2748, 53);
	test_wpyear(2749, 52);
	test_wpyear(2750, 52);
	test_wpyear(2751, 52);
	test_wpyear(2752, 52);
	test_wpyear(2753, 53);
	test_wpyear(2754, 52);
	test_wpyear(2755, 52);
	test_wpyear(2756, 52);
	test_wpyear(2757, 52);
	test_wpyear(2758, 52);
	test_wpyear(2759, 53);
	test_wpyear(2760, 52);
	test_wpyear(2761, 52);
	test_wpyear(2762, 52);
	test_wpyear(2763, 52);
	test_wpyear(2764, 53);
	test_wpyear(2765, 52);
	test_wpyear(2766, 52);
	test_wpyear(2767, 52);
	test_wpyear(2768, 52);
	test_wpyear(2769, 52);
	test_wpyear(2770, 53);
	test_wpyear(2771, 52);
	test_wpyear(2772, 52);
	test_wpyear(2773, 52);
	test_wpyear(2774, 52);
	test_wpyear(2775, 52);
	test_wpyear(2776, 53);
	test_wpyear(2777, 52);
	test_wpyear(2778, 52);
	test_wpyear(2779, 52);
	test_wpyear(2780, 52);
	test_wpyear(2781, 53);
	test_wpyear(2782, 52);
	test_wpyear(2783, 52);
	test_wpyear(2784, 52);
	test_wpyear(2785, 52);
	test_wpyear(2786, 52);
	test_wpyear(2787, 53);
	test_wpyear(2788, 52);
	test_wpyear(2789, 52);
	test_wpyear(2790, 52);
	test_wpyear(2791, 52);
	test_wpyear(2792, 53);
	test_wpyear(2793, 52);
	test_wpyear(2794, 52);
	test_wpyear(2795, 52);
	test_wpyear(2796, 52);
	test_wpyear(2797, 52);
	test_wpyear(2798, 53);
	test_wpyear(2799, 52);
	test_wpyear(2800, 52);
	std::cout << "Years 2701 to 2800 cleared...";
	std::cout << '\n';
	test_wpyear(2801, 52);
	test_wpyear(2802, 52);
	test_wpyear(2803, 52);
	test_wpyear(2804, 53);
	test_wpyear(2805, 52);
	test_wpyear(2806, 52);
	test_wpyear(2807, 52);
	test_wpyear(2808, 52);
	test_wpyear(2809, 53);
	test_wpyear(2810, 52);
	test_wpyear(2811, 52);
	test_wpyear(2812, 52);
	test_wpyear(2813, 52);
	test_wpyear(2814, 52);
	test_wpyear(2815, 53);
	test_wpyear(2816, 52);
	test_wpyear(2817, 52);
	test_wpyear(2818, 52);
	test_wpyear(2819, 52);
	test_wpyear(2820, 53);
	test_wpyear(2821, 52);
	test_wpyear(2822, 52);
	test_wpyear(2823, 52);
	test_wpyear(2824, 52);
	test_wpyear(2825, 52);
	test_wpyear(2826, 53);
	test_wpyear(2827, 52);
	test_wpyear(2828, 52);
	test_wpyear(2829, 52);
	test_wpyear(2830, 52);
	test_wpyear(2831, 52);
	test_wpyear(2832, 53);
	test_wpyear(2833, 52);
	test_wpyear(2834, 52);
	test_wpyear(2835, 52);
	test_wpyear(2836, 52);
	test_wpyear(2837, 53);
	test_wpyear(2838, 52);
	test_wpyear(2839, 52);
	test_wpyear(2840, 52);
	test_wpyear(2841, 52);
	test_wpyear(2842, 52);
	test_wpyear(2843, 53);
	test_wpyear(2844, 52);
	test_wpyear(2845, 52);
	test_wpyear(2846, 52);
	test_wpyear(2847, 52);
	test_wpyear(2848, 53);
	test_wpyear(2849, 52);
	test_wpyear(2850, 52);
	test_wpyear(2851, 52);
	test_wpyear(2852, 52);
	test_wpyear(2853, 52);
	test_wpyear(2854, 53);
	test_wpyear(2855, 52);
	test_wpyear(2856, 52);
	test_wpyear(2857, 52);
	test_wpyear(2858, 52);
	test_wpyear(2859, 52);
	test_wpyear(2860, 53);
	test_wpyear(2861, 52);
	test_wpyear(2862, 52);
	test_wpyear(2863, 52);
	test_wpyear(2864, 52);
	test_wpyear(2865, 53);
	test_wpyear(2866, 52);
	test_wpyear(2867, 52);
	test_wpyear(2868, 52);
	test_wpyear(2869, 52);
	test_wpyear(2870, 52);
	test_wpyear(2871, 53);
	test_wpyear(2872, 52);
	test_wpyear(2873, 52);
	test_wpyear(2874, 52);
	test_wpyear(2875, 52);
	test_wpyear(2876, 53);
	test_wpyear(2877, 52);
	test_wpyear(2878, 52);
	test_wpyear(2879, 52);
	test_wpyear(2880, 52);
	test_wpyear(2881, 52);
	test_wpyear(2882, 53);
	test_wpyear(2883, 52);
	test_wpyear(2884, 52);
	test_wpyear(2885, 52);
	test_wpyear(2886, 52);
	test_wpyear(2887, 52);
	test_wpyear(2888, 53);
	test_wpyear(2889, 52);
	test_wpyear(2890, 52);
	test_wpyear(2891, 52);
	test_wpyear(2892, 52);
	test_wpyear(2893, 53);
	test_wpyear(2894, 52);
	test_wpyear(2895, 52);
	test_wpyear(2896, 52);
	test_wpyear(2897, 52);
	test_wpyear(2898, 52);
	test_wpyear(2899, 53);
	test_wpyear(2900, 52);
	std::cout << "Years 2801 to 2900 cleared...";
	std::cout << ' ';
	test_wpyear(2901, 52);
	test_wpyear(2902, 52);
	test_wpyear(2903, 52);
	test_wpyear(2904, 52);
	test_wpyear(2905, 53);
	test_wpyear(2906, 52);
	test_wpyear(2907, 52);
	test_wpyear(2908, 52);
	test_wpyear(2909, 52);
	test_wpyear(2910, 52);
	test_wpyear(2911, 53);
	test_wpyear(2912, 52);
	test_wpyear(2913, 52);
	test_wpyear(2914, 52);
	test_wpyear(2915, 52);
	test_wpyear(2916, 53);
	test_wpyear(2917, 52);
	test_wpyear(2918, 52);
	test_wpyear(2919, 52);
	test_wpyear(2920, 52);
	test_wpyear(2921, 52);
	test_wpyear(2922, 53);
	test_wpyear(2923, 52);
	test_wpyear(2924, 52);
	test_wpyear(2925, 52);
	test_wpyear(2926, 52);
	test_wpyear(2927, 52);
	test_wpyear(2928, 53);
	test_wpyear(2929, 52);
	test_wpyear(2930, 52);
	test_wpyear(2931, 52);
	test_wpyear(2932, 52);
	test_wpyear(2933, 53);
	test_wpyear(2934, 52);
	test_wpyear(2935, 52);
	test_wpyear(2936, 52);
	test_wpyear(2937, 52);
	test_wpyear(2938, 52);
	test_wpyear(2939, 53);
	test_wpyear(2940, 52);
	test_wpyear(2941, 52);
	test_wpyear(2942, 52);
	test_wpyear(2943, 52);
	test_wpyear(2944, 53);
	test_wpyear(2945, 52);
	test_wpyear(2946, 52);
	test_wpyear(2947, 52);
	test_wpyear(2948, 52);
	test_wpyear(2949, 52);
	test_wpyear(2950, 53);
	test_wpyear(2951, 52);
	test_wpyear(2952, 52);
	test_wpyear(2953, 52);
	test_wpyear(2954, 52);
	test_wpyear(2955, 52);
	test_wpyear(2956, 53);
	test_wpyear(2957, 52);
	test_wpyear(2958, 52);
	test_wpyear(2959, 52);
	test_wpyear(2960, 52);
	test_wpyear(2961, 53);
	test_wpyear(2962, 52);
	test_wpyear(2963, 52);
	test_wpyear(2964, 52);
	test_wpyear(2965, 52);
	test_wpyear(2966, 52);
	test_wpyear(2967, 53);
	test_wpyear(2968, 52);
	test_wpyear(2969, 52);
	test_wpyear(2970, 52);
	test_wpyear(2971, 52);
	test_wpyear(2972, 53);
	test_wpyear(2973, 52);
	test_wpyear(2974, 52);
	test_wpyear(2975, 52);
	test_wpyear(2976, 52);
	test_wpyear(2977, 52);
	test_wpyear(2978, 53);
	test_wpyear(2979, 52);
	test_wpyear(2980, 52);
	test_wpyear(2981, 52);
	test_wpyear(2982, 52);
	test_wpyear(2983, 52);
	test_wpyear(2984, 53);
	test_wpyear(2985, 52);
	test_wpyear(2986, 52);
	test_wpyear(2987, 52);
	test_wpyear(2988, 52);
	test_wpyear(2989, 53);
	test_wpyear(2990, 52);
	test_wpyear(2991, 52);
	test_wpyear(2992, 52);
	test_wpyear(2993, 52);
	test_wpyear(2994, 52);
	test_wpyear(2995, 53);
	test_wpyear(2996, 52);
	test_wpyear(2997, 52);
	test_wpyear(2998, 52);
	test_wpyear(2999, 52);
	test_wpyear(3000, 52);
	std::cout << "Years 2901 to 3000 cleared..." << '\n'
	          << "All week_per_year() tests were passed!" << '\n';
}

