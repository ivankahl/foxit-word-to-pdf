#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <cstdlib>
#include <stdlib.h>

#include "common/fs_common.h"
#include "addon/conversion/fs_convert.h"
using namespace std;
using namespace foxit;
using namespace common;
using namespace pdf;
using namespace foxit::common;
using namespace foxit::addon::conversion;

int main(int argc, char *argv[])
{
    // The value of "sn" can be got from "gsdk_sn.txt" (the string after "SN=").
    const char *sn = std::getenv("FOXIT_SN");
    // The value of "key" can be got from "gsdk_key.txt" (the string after "Sign=").
    const char *key = std::getenv("FOXIT_KEY");

    // Initialize the library before using it
    foxit::ErrorCode code = Library::Initialize(sn, key);
    if (code != foxit::e_ErrSuccess)
    {
        return FALSE;
    }

    // Get the parameters for the conversion
    Word2PDFSettingData word2PdfSettingData;
    // The first positional command line parameter contains the DOCX file path
    WString doc;
    doc.ConvertFrom(argv[1]);
    // The second positional command line parameter contains the PDF file's desired path
    WString pdf;          
    pdf.ConvertFrom(argv[2]);

    // Convert the document
    Convert::FromWord(doc, L"", pdf, L"/opt/libreoffice6.4/program", word2PdfSettingData);

    // Release the library when finished
    Library::Release();

    // Exit with 0 to signify everything executed successfully.
    exit(0);
}