#if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
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
 * @file fs_ocr.h
 * @brief Header file for OCR related classes and methods.
 */

#ifndef FS_OCR_H_
#define FS_OCR_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"

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
 * @brief OCR namespace.
 */
namespace ocr {
/**
 * OCR add-on module can be used to convert text content of image to searchable text or editable text
 * in a PDF page or a PDF document.
 * Before using OCR module, user should first prepare OCR resource folder as described in "Foxit PDF SDK Developer Guide.pdf" document.
 * Before initializing OCR engine and using any classes or methods in this module, please ensure
 * Foxti PDF SDK has been initialized successfully by function @link common::Library::Initialize @endlink
 * with a key including "OCR" module.<br>
 * Currently, OCR module only supports Windows and Linux64 system.
 *
 * @see @link common::Library @endlink
 */
class OCREngine FS_FINAL : public Object {
 public:
  /**
   * @brief Initialize OCR engine.
   *
   * @details This should be called successfully before any other methods in OCR add-on module.
   *
   * @param[in] ocr_resource_path  File path of ocr resource folder. It should not be an empty string.
   *                               Please refer to "Foxit PDF SDK Developer Guide.pdf" document for more details.
   *
   * @note If module "OCR" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using OCR related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoOCRModuleRight @endlink.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrNoOCRModuleRight @endlink means Foxit PDF SDK has not been initialized with
   *         a key including "OCR" module.<br>
   *         @link foxit::e_ErrParam @endlink means parameter <i>ocrt_resource_path</i> is an empty string.<br>
   *         For more information about error code values, please refer to values starting from
   *         @link foxit::e_ErrSuccess @endlink.
   */
  static ErrorCode Initialize(const wchar_t* ocr_resource_path);

  /**
   * @brief Release OCR engine.
   *
   * @details This function can be called to release OCR engine when no need to use it any more
   *          before Foxit PDF SDK is released.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Set log file for OCR engine.
   *
   * @details This function is to set the log file for OCR engine, not for Foxit PDF SDK.
   *          If user wants to set log file for Foxit PDF SDK, please refer to function
   *          @link common::Library::SetLogFile @endlink.
   *
   * @param[in] log_file_path  A log file path. If this is an empty string, that means stop the log for OCR engine.
   *
   * @return None.
   */
  static void SetLogFile(const char* log_file_path);

  /**
   * @brief Set log file for OCR engine.
   *
   * @details This function is to set the log file for OCR engine, not for Foxit PDF SDK.
   *          If user wants to set log file for Foxit PDF SDK, please refer to function
   *          @link common::Library::SetLogFile @endlink.
   *
   * @param[in] log_file_path  A log file path. If this is an empty string, that means stop the log for OCR engine.
   *
   * @return None.
   */
  static void SetLogFile(const wchar_t* log_file_path);

  /**
   * @brief Set the name of languages which would be included in the language database for doing OCR.
   *
   * @details Current supported languages:
   *          <ul>
   *          <li>When CJK language resources are used, support Chinese-Simplified, Chinese-Traditional, Japanese, Korean.</li>
   *          <li>When other language resources are used, support Basque, Bulgarian, Catalan, Croatian, Czech, Danish,
   *              Dutch, English , Estonian, Faeroese, Finnish, French, Galician, German, Greek, Hebrew, Hungarian,
   *              Icelandic, Italian, Latvian(Lettish), Lithuanian, Macedonian, Maltese, Norwegian, Polish, Portuguese,
   *              Romanian, Russian, Serbian, Slovak, Slovenian, Spanish, Swedish, Thai, Turkish, Ukrainian.</li>
   *          </ul>
   *          If no any language is set by this function, Foxit PDF SDK will use "English" by default.
   *
   * @param[in] languages  Language names. This should not be an empty string.
   *                       This can contain one language name or several language names separated with commas.
   *                       For example, "English" means English only, and "English,French" means English and French only.
   *
   * @return None.
   */
  static void SetLanguages(const wchar_t* languages);
};

/** This class represents setting data used for OCR. */
class OCRSettingData FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor.
   */
  OCRSettingData(){};

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] pdf_doc      A valid PDF document.
   * @param[in] page_range   The range of pages that need to be OCR.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited.
   */
  OCRSettingData(pdf::PDFDoc pdf_doc, const common::Range& page_range, bool is_editable) {
    this->pdf_doc = pdf_doc;
    this->page_range = page_range;
    this->is_editable = is_editable;
  }

  /**
   * @brief Set value.
   *
   * @param[in] pdf_doc      A valid PDF document.
   * @param[in] page_range   The range of pages that need to be OCR.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited.
   *
   * @return None.
   */
  void Set(pdf::PDFDoc pdf_doc, const common::Range& page_range, bool is_editable) {
    this->pdf_doc = pdf_doc;
    this->page_range = page_range;
    this->is_editable = is_editable;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another OCR setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OCRSettingData& operator=(const OCRSettingData& data) {
    pdf_doc = data.pdf_doc;
    page_range = data.page_range;
    is_editable = data.is_editable;
    return (*this);
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another OCR setting data object, whose value would be assigned to current object.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const OCRSettingData& data) {
    if (pdf_doc != data.pdf_doc || page_range != data.page_range || is_editable != data.is_editable)
      return true;
    return false;
  }

  /** @brief A valid PDF document that need to be OCR. */
  pdf::PDFDoc pdf_doc;

  /** @brief The range of pages that need to be OCR. */
  common::Range page_range;

  /** @brief Decide whether the OCR result is editable. <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited. */
  bool is_editable;
};

/** This class represents an array of @link OCRSettingData @endlink objects. */
FSDK_DEFINE_ARRAY(OCRSettingDataArray, OCRSettingData)

/**
 * This class indicates that it is used to collect the information set of suspicious results that exist after OCR
 * recognition is completed. Use this information to quickly locate the page and coordinate position of the suspicious
 * information.
 */
class OCRSuspectInfo FS_FINAL : public Object {
 public:
  /** @brief The index of page. */
  int page_index;

  /** @brief The box rectangle, in [PDF coordinate system] (@ref PDFPage) for suspicious words */
  foxit::RectF words_rect;

  /** @brief Suspicious words after OCR recognition. */
  WString suspect_words;
};

/** This class represents an array of OCR suspicious information. */
FSDK_DEFINE_ARRAY(OCRSuspectInfoArray, OCRSuspectInfo)

/**
 * This class is used to do OCR for a PDF page or a PDF document.
 * Please ensure OCR engine has been initialized before using this class.
 *
 * @see @link OCREngine @endlink
 */
class OCR FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   */
  OCR();

  /**
   * @brief Constructor, with another ocr object.
   *
   * @param[in] other  Another ocr object.
   */
  OCR(const OCR& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OCR(FS_HANDLE handle);
  /** @brief Destructor. */
  ~OCR();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another ocr object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OCR& operator = (const OCR& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another ocr object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OCR& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another ocr object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OCR& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief OCR a PDF page.
   *
   * @details After this function succeeds, the PDF page content may be changed and
   *          the input PDF page is recommended to be re-parsed.
   *
   * @param[in] pdf_page     A valid PDF page object. This PDF page should have been parsed.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edit.
   *
   * @return None.
   */
  void OCRPDFPage(pdf::PDFPage pdf_page, bool is_editable);

  /**
   * @brief OCR each page of a PDF document.
   *
   * @details After this function succeeds, the PDF page content may be changed. It is better to parse or re-parse
   *          PDF pages in the input PDF document before using these pages.
   *
   * @param[in] pdf_doc      A valid PDF document object.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited.
   *
   * @return None.
   */
  void OCRPDFDocument(pdf::PDFDoc pdf_doc, bool is_editable);
#if defined(_WIN32) || defined(_WIN64)
  /**
   * @brief OCR multiple pages of multiple PDF documents.
   *
   * @details This function can be used to batch process multiple documents or pages.
   *          Users can set documents and page ranges via @link OCRSettingDataArray @endlink.
   *          The time performance of this function will be better than calling @link OCRPDFDocument @endlink or @link
   * OCR::OCRPDFPage @endlink multiple times when dealing with a large number of documents or pages. After successful
   * execution, the page content may be changed, it is better to parse or re-parse the PDF pages before using these
   * pages.
   *
   * @param[in] settingdata_array  An array of @link OCRSettingData @endlink objects, if the parameter
   *                               <i>page_range</i> of @link OCRSettingData @endlink object is empty, that
   *                               means OCR each page of the PDF document.
   *
   * @return None.
   */
  void OCRPDFDocuments(const ocr::OCRSettingDataArray& settingdata_array);
#endif

  /**
   * @brief Get OCR suspicious information.
   *
   * @details  The parameter <i>ocred_pdf_doc</i> is a valid PDF document that should have been ocred.
   *
   * @param[in] ocred_pdf_doc   A valid PDF document object. 
   *
   * @return An array of @link OCRSuspectInfo @endlink objects, If its value is empty, that means the document OCR has no suspicious information.
   */
  OCRSuspectInfoArray GetOCRSuspectsInfo(pdf::PDFDoc ocred_pdf_doc);
};

}  // namespace ocr
}  // namespace addon
}  // namespace foxit

#endif  // FS_OCR_H_

#endif  // #if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
