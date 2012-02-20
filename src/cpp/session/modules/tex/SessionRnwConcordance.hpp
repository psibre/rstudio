/*
 * SessionRnwConcordance.hpp
 *
 * Copyright (C) 2009-11 by RStudio, Inc.
 *
 * This program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */

#ifndef SESSION_MODULES_RNW_CONCORDANCE_HPP
#define SESSION_MODULES_RNW_CONCORDANCE_HPP

#include <string>
#include <vector>

#include <boost/utility.hpp>

#include <core/FilePath.hpp>
#include <core/tex/TexLogParser.hpp>

namespace core {
   class Error;
}
 
namespace session {
namespace modules { 
namespace tex {
namespace rnw_concordance {

class Concordance
{
public:
   Concordance()
      : offset_(0)
   {
   }

   // COPYING: via compiler

   core::Error parse(const core::FilePath& sourceFile,
                     const std::string& input,
                     const core::FilePath& baseDir);

   bool empty() const { return mapping_.empty(); }

   const core::FilePath& outputFile() const { return outputFile_; }

   const core::FilePath& inputFile() const { return inputFile_; }

   int offset() const { return offset_; }

   // checked access to rnw lines from tex lines
   int rnwLine(std::size_t texLine) const
   {
      // subtract 1 to normalize lines to C array indexes
      texLine--;

      // then substract the offset (which was the starting line
      // number of the output generated by the input file)
      texLine -= offset_;

      // return the mapping (but return 1 if it is out of range)
      if (texLine >= 0 && texLine < mapping_.size())
         return mapping_[texLine];
      else
         return -1;
   }

private:
   core::FilePath outputFile_;
   core::FilePath inputFile_;
   std::size_t offset_;
   std::vector<int> mapping_;
};

class FileAndLine
{
public:
   FileAndLine()
      : line_(-1)
   {
   }

   FileAndLine(const core::FilePath& filePath, int line)
      : filePath_(filePath), line_(line)
   {
   }
   ~FileAndLine() {}
   // COPYING: via compiler

   bool empty() const { return filePath_.empty(); }

   const core::FilePath& filePath() const { return filePath_; }
   int line() const { return line_; }

private:
   core::FilePath filePath_;
   int line_;
};

class Concordances
{
public:
   Concordances() {}
   ~Concordances() {}
   // COPYING: via compiler

   void add(Concordance& concordance)
   {
      concordances_.push_back(concordance);
   }

   FileAndLine lookup(const FileAndLine& texFileAndLine) const;
   core::tex::LogEntry fixup(const core::tex::LogEntry& entry,
                             bool* pSuccess=NULL) const;

private:
   std::vector<Concordance> concordances_;
};

void removePrevious(const core::FilePath& rnwFile);

core::Error readIfExists(const core::FilePath& rnwFile,
                         Concordances* pConcordances);

} // namespace rnw_concordance
} // namespace tex
} // namespace modules
} // namesapce session

#endif // SESSION_MODULES_RNW_CONCORDANCE_HPP