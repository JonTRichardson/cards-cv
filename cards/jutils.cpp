#define JUTILS_CPP_VERSION   "ver 1+"

#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "jutils.hpp"

using std::cout;
using std::endl;

void j_print_matchMethod(const int method)
{
    //cout <<JUTILS_CPP_VERSION << endl;

    switch (method)
    {
		case CV_TM_SQDIFF:
			cout << "CV_TM_SQDIFF("<< method<<")\n";
			break;
		case CV_TM_SQDIFF_NORMED:
			cout << "CV_TM_SQDIFF_NORMED("<< method<<")\n";
			break;
		case CV_TM_CCORR:
			cout << "CV_TM_CCORR(" << method<<")\n";
			break;
		case CV_TM_CCORR_NORMED:
			cout << "CV_TM_CCORR_NORMED("<< method<<")\n";
			break;
		case CV_TM_CCOEFF:
			cout << "CV_TM_CCOEFF("<< method<<")\n";
			break;
		case CV_TM_CCOEFF_NORMED:
			cout << "CV_TM_CCOEFF_NORMED("<< method<<")\n";
			break;
        default:
			cout << "unknown method:("<< method <<")\n";
    }
}
