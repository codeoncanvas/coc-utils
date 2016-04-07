/*

Helper functions to use in conjunction with Cinder and OF loggers

Example Cinder usage (requires that folder exist):

if (useLogFiles) {
	string logPath = getAssetPath("").generic_string() + "/logs/" + coc::getLogFileName();
	log::makeLogger<log::LoggerFile>(logPath);
	coc::limitLogFiles(getAssetPath("").generic_string() + "/logs");
	CI_LOG_I("\n\nAPPLICATION STARTED\n");
}

Todo: Example OF usage

*/

#pragma once

#ifdef COC_CI
#include "cinder/app/App.h"
#endif

#ifdef COC_OF
#include "ofMain.h"
#endif


namespace coc {


#ifdef COC_CI

		static std::vector<std::string> listDirectory(std::string _path, bool _verbose = false) {

			std::vector<std::string> files;
			boost::filesystem::path p(_path);

			if (_verbose) ci::app::console() << "About to list " << _path << ":\n";

			if (p.generic_string() != "") {

				for (boost::filesystem::directory_iterator it(p); it != boost::filesystem::directory_iterator(); ++it)
				{
					if (boost::filesystem::is_regular_file(*it))
					{
						std::string fileName = it->path().filename().string();

						if (fileName[0] != '.')//ignore hidden files
						{
							files.push_back(fileName);
							if (_verbose) ci::app::console() << "\t" << fileName << std::endl;
						}
					}
				}
			}

			return files;
		}

#endif

		// output format is YYYY-MM-DD
		static std::string getLogFileName( std::string _ext = "log" ) {

			time_t timeSinceEpoch = time(NULL);
			struct tm *now = localtime(&timeSinceEpoch);

			char result[100];
			strftime(result, sizeof(result), "%Y-%m-%d", now);
			std::string str(result);

			return str + "." + _ext;

		}

		static void limitLogFiles( std::string _path, int _i = 30) {
			
			std::vector<std::string> files;

			#ifdef COC_CI
			files = listDirectory(_path);
			#endif

			#ifdef COC_OF
				//todo: files = OF equivalent 
			#endif
		
			while (files.size() > _i) {
				std::string path = _path + "/" + files[0];
				std::remove(path.c_str());
				files.erase(files.begin());
			}

		}



}//namespace coc