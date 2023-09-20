/**
 * Copyright (C) 2003-2022, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_pdf2office.h
 * @brief Header file for PDF2Office related definitions and classes.
 */
/**
 * Copyright (C) 2003-2023, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_pdf2office.h
 * @brief Header file for converting PDF to office related definitions and classes.
 */
#ifndef FS_PDF2OFFICE_H_
#define FS_PDF2OFFICE_H_
#if defined(_WIN32) || defined(_WIN64) || (defined(__linux__) && !defined(__ANDROID__))
#include "common/fs_common.h"

/**
* @brief Foxit namespace.
*
* @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
*/
namespace foxit {
/**
 * @brief Add-on namespace.
 */
namespace addon {
/**
 * @brief Conversion namespace.
 */
namespace conversion {
/**
 * @brief pdf2office namespace.
 */
namespace pdf2office {
/** This class represents setting data used for converting PDF to Office(Word, Excel or PowerPoint) format file. */
class PDF2OfficeSettingData FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  PDF2OfficeSettingData()
    : enable_ml_recognition(false) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] metrics_data_folder_path  A valid path of a folder which contains metrics data files. This should not be an empty string. 
   *                                      These metrics data files are used to simulate the office format document typesetting process during conversion.
   *                                      They are offered in the "res/metrics_data" folder of the Foxit PDF Conversion SDK package.
   * @param[in] enable_ml_recognition     A boolean value which indicates whether enable machine learning-based recognition functionality.
   *                                      <b>true</b> means enable machine learning-based recognition functionality to identify borderless tables in PDF documents. 
   *                                      In order to convert the tables better, it will draw a black border with a width of 1 on the recognized borderless table.
   *                                      This will be improved in subsequent versions.
   *                                      And this recognition functionality will be executed on the server side and return the relevant results when it is done. 
   *                                      <b>false</b> means disable machine learning-based recognition functionality.
   *                                      And the recognition functionality not based on machine learning will be enabled.
   *
   * @note Our machine learning-based technology for identifying borderless tables uses HTTPS and requires a network connection to send the images of the rendered PDF pages to our server during the conversion process.   
   */
  PDF2OfficeSettingData(const wchar_t* metrics_data_folder_path, bool enable_ml_recognition) {
    this->metrics_data_folder_path = metrics_data_folder_path;
    this->enable_ml_recognition = enable_ml_recognition;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PDF-to-Office setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF2OfficeSettingData &operator = (const PDF2OfficeSettingData& data) {
    metrics_data_folder_path = data.metrics_data_folder_path;
    enable_ml_recognition = data.enable_ml_recognition;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] metrics_data_folder_path  A valid path of a folder which contains metrics data files. This should not be an empty string. 
   *                                      These metrics data files are used to simulate the office format document typesetting process during conversion.
   *                                      They are offered in the "res/metrics_data" folder of the Foxit PDF Conversion SDK package.
   * @param[in] enable_ml_recognition     A boolean value which indicates whether enable machine learning-based recognition functionality.
   *                                      <b>true</b> means enable machine learning-based recognition functionality to identify borderless tables in PDF documents. 
   *                                      In order to convert the tables better, it will draw a black border with a width of 1 on the recognized borderless table.
   *                                      This will be improved in subsequent versions.
   *                                      And this recognition functionality will be executed on the server side and return the relevant results when it is done. 
   *                                      <b>false</b> means disable machine learning-based recognition functionality.
   *                                      And the recognition functionality not based on machine learning will be enabled.
   *
   * @note Our machine learning-based technology for identifying borderless tables uses HTTPS and requires a network connection to send the images of the rendered PDF pages to our server during the conversion process.
   *
   * @return None.
   */
  void Set(const wchar_t* metrics_data_folder_path, bool enable_ml_recognition) {
    this->metrics_data_folder_path = metrics_data_folder_path;
    this->enable_ml_recognition = enable_ml_recognition;
  }

  /**
   * @brief A valid path of a folder which contains metrics data files. This should not be an empty string.
   *
   * @details These metrics data files are used to simulate the office format document typesetting process during conversion.
   *          They are offered in the "res/metrics_data" folder of the Foxit PDF Conversion SDK package.
   */
  WString metrics_data_folder_path;

  /**
   * @brief A boolean value which indicates whether enable machine learning-based recognition functionality.
   *
   * @details <b>true</b> means enable machine learning-based recognition functionality to identify borderless tables in PDF documents.
   *          And this recognition functionality will be executed on the server side and return the relevant results when it is done.
   *          In order to convert the tables better, it will draw a black border with a width of 1 on the recognized borderless table.
   *          This will be improved in subsequent versions.
   *          <b>false</b> means disable machine learning-based recognition functionality.
   *          And the recognition functionality not based on machine learning will be enabled.
   *
   * @note Our machine learning-based technology for identifying borderless tables uses HTTPS and requires a network connection to send the images of the rendered PDF pages to our server during the conversion process.
   */
  bool enable_ml_recognition;
};

/**
 * This class represents a callback object used to pause and notify the conversion progress during the converting process.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ConvertCallback {
 public:
  /**
   * @brief A callback function used to pause the current conversion progress.
   *
   * @return <b>true</b> means to pause now, while <b>false</b> means not to pause now.
   */
  virtual bool NeedToPause() = 0;
  
  /**
   * @brief A callback function used to notify the current conversion progress.
   *
   * @param[in] converted_count  The converted page count.
   * @param[in] total_count      The total page count.
   *
   * @return None.
   */
  virtual void ProgressNotify(int converted_count, int total_count) = 0;
};

/**
 * This class can be used to convert PDF files to Office(Word, Excel or PowerPoint) format files.
 * Before using "Conversion" module, please ensure the resource folders named "res" and "lib" in the Foxit PDF Conversion SDK package is valid.
 * Before using methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "PDF2Office" module.
 *
 * @see @link common::Library @endlink
 */
class PDF2Office FS_FINAL : public Base {
 public:
  /**
   * @brief Initialize Foxit PDF Conversion SDK Library.
   *
   * @details During the life-cycle of "pdf2office" module, this function can only be called once and
   *          should be called first before any other functions in "pdf2office" module can be called.
   *
   * @param[in] library_path  Path of Foxit PDF Conversion SDK library. This should not be an empty string.
   *
   * @return None.
   */
  static void Initialize(const wchar_t* library_path);

  /**
   * @brief Release all resource allocated by Foxit PDF Conversion SDK Library.
   *
   * @details When the user does not use "pdf2office" module, this function should be called to release all memory blocks allocated by the library.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Start to convert a PDF file to a Word format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to DOCX format file.
   *
   * @param[in] src_pdf_path          Path of a PDF file. This should not be an empty string.
   * @param[in] src_pdf_password      Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_word_file_path  Path of the saved Word format file as conversion result. This should not be an empty string.
   *                                  If the suffix name of the saved Word format file is not "docx", a new suffix named "docx" will be added to the original file name.
   * @param[in] setting_data          Setting data used for converting.
   * @param[in] convert_callback      A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                  to pause and notify the conversion progress during the converting process.
   *                                  This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                  If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                  object implemented by user.<br>
   *                                  Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartConvertToWord(const wchar_t* src_pdf_path, const wchar_t* src_pdf_password, const wchar_t* saved_word_file_path, 
                            const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
   
  /**
   * @brief Start to convert a PDF file to a Word format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to DOCX format file.
   *
   * @param[in] src_pdf_reader          A @link ReaderCallback @endlink object which is implemented by user to
   *                                    load a PDF document. It should not be <b>NULL</b>.
   * @param[in] src_pdf_password        Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_word_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user 
   *                                    to read the contents of the converted Word format file. It should not be <b>NULL</b>.
   * @param[in] setting_data            Setting data used for converting.
   * @param[in] convert_callback        A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                    to pause and notify the conversion progress during the converting process.
   *                                    This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                    If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                    object implemented by user.<br>
   *                                    Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished..
   */
  static common::Progressive StartConvertToWord(common::file::ReaderCallback* src_pdf_reader, const wchar_t* src_pdf_password, common::file::StreamCallback* saved_word_file_stream, 
                            const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
  
  /**
   * @brief Start to convert a PDF file to a Excel format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to XLSX format file.
   *
   * @param[in] src_pdf_path           Path of a PDF file. This should not be an empty string.
   * @param[in] src_pdf_password       Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_excel_file_path  Path of the saved Excel format file as conversion result. This should not be an empty string.
   *                                   If the suffix name of the saved Excel format file is not "xlsx", a new suffix named "xlsx" will be added to the original file name.
   * @param[in] setting_data           Setting data used for converting.
   * @param[in] convert_callback       A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                   to pause and notify the conversion progress during the converting process.
   *                                   This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                   If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                   object implemented by user.<br>
   *                                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartConvertToExcel(const wchar_t* src_pdf_path, const wchar_t* src_pdf_password, const wchar_t* saved_excel_file_path, 
                             const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
   
  /**
   * @brief Start to convert a PDF file to a Excel format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to XLSX format file.
   *
   * @param[in] src_pdf_reader           A @link ReaderCallback @endlink object which is implemented by user to
   *                                     load a PDF document. It should not be <b>NULL</b>.
   * @param[in] src_pdf_password         Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_excel_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user 
   *                                     to read the contents of the converted Excel format file. It should not be <b>NULL</b>.
   * @param[in] setting_data             Setting data used for converting.
   * @param[in] convert_callback         A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                     to pause and notify the conversion progress during the converting process.
   *                                     This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                     If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                     object implemented by user.<br>
   *                                     Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartConvertToExcel(common::file::ReaderCallback* src_pdf_reader, const wchar_t* src_pdf_password, common::file::StreamCallback* saved_excel_file_stream, 
                             const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
  
  /**
   * @brief Start to convert a PDF file to a PowerPoint format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to PPTX format file.
   *
   * @param[in] src_pdf_path         Path of a PDF file. This should not be an empty string.
   * @param[in] src_pdf_password     Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_ppt_file_path  Path of the saved PowerPoint format file as conversion result. This should not be an empty string.
   *                                 If the suffix name of the saved PowerPoint format file is not "pptx", a new suffix named "pptx" will be added to the original file name.
   * @param[in] setting_data         Setting data used for converting.
   * @param[in] convert_callback     A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                 to pause and notify the conversion progress during the converting process.
   *                                 This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                 If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                 object implemented by user.<br>
   *                                 Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartConvertToPowerPoint(const wchar_t* src_pdf_path, const wchar_t* src_pdf_password, const wchar_t* saved_ppt_file_path, 
                                  const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
  
  /**
   * @brief Start to convert a PDF file to a PowerPoint format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to PPTX format file.
   *
   * @param[in] src_pdf_reader         A @link ReaderCallback @endlink object which is implemented by user to
   *                                   load a PDF document. It should not be <b>NULL</b>.
   * @param[in] src_pdf_password       Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_ppt_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user 
   *                                   to read the contents of the converted PowerPoint format file. It should not be <b>NULL</b>.
   * @param[in] setting_data           Setting data used for converting.
   * @param[in] convert_callback       A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                   to pause and notify the conversion progress during the converting process.
   *                                   This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                   If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                   object implemented by user.<br>
   *                                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartConvertToPowerPoint(common::file::ReaderCallback* src_pdf_reader, const wchar_t* src_pdf_password, common::file::StreamCallback* saved_ppt_file_stream, 
                                  const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);

};

}  // namespace pdf2office
}  // namespace conversion
}  // namespace addon
}  // namespace foxit

#endif //defined(WIN32) 
#endif
