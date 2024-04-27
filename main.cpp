#include <iostream>
//#include <lame/lame.h>
#include <filesystem>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

//#define MP3_SIZE 8192
//#define PCM_SIZE 8192

string escapePath(const std::string& path) {
    std::string escapedPath;
    for (char c : path) {
        if (c == ' ' || c == '\\' || c == '"') {
            escapedPath.push_back('\\');
        }
        escapedPath.push_back(c);
    }
    return escapedPath;
}

void convertMP3ToWAV(const fs::path& inputFile, const fs::path& outputFile) {
//    // Open the MP3 file
//    FILE *mp3_file = fopen(inputFile.c_str(), "rb");
//    if (!mp3_file) {
//        cout << "Error: Could not open input file." << endl;
//        return;
//    }
//
//    // Initialize libmp3lame
//    lame_t lame = lame_init();
//
//    // Set input and output formats
//    lame_set_in_samplerate(lame, 44100); // Input sample rate
//    lame_set_num_channels(lame, 2);       // Number of channels (stereo)
//    lame_set_out_samplerate(lame, 44100); // Output sample rate
//    lame_set_num_channels(lame, 2);       // Number of output channels
//    lame_set_quality(lame, 2);            // Set the MP3 quality
//    lame_init_params(lame);
//
//    // Open the output WAV file
//    FILE *wav_file = fopen(outputFile.c_str(), "wb");
//    if (!wav_file) {
//        cout << "Error: Could not open output file." << endl;
//        lame_close(lame);
//        fclose(mp3_file);
//        return;
//    }
//
//    // Decode MP3 and write to WAV
//    int read, write;
//    short int pcm_buffer[PCM_SIZE*2];
//    unsigned char mp3_buffer[MP3_SIZE];
//
//    do {
//        read = fread(mp3_buffer, 2*sizeof(short int), MP3_SIZE, mp3_file); // Read from mp3_file
//        if (read == 0)
//            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
//        else
//            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
//        fwrite(pcm_buffer, write, 1, wav_file); // Write to wav_file
//    } while (read != 0);
//
//    // Clean up
//    fclose(mp3_file);
//    fclose(wav_file);
//    lame_close(lame);

    string inputFilename = escapePath(inputFile.string());
    string outputFilename = escapePath(outputFile.string());

    string command = "lame --decode " + inputFilename + " -b 32 " + outputFilename + " --quiet";

    system(command.c_str());
}

int main() {
    fs::path current_path = fs::current_path().parent_path();
    fs::path input_path = current_path / "input";
    fs::path output_path = current_path / "output";

    for (const auto& entry : fs::directory_iterator(input_path)) {
        const fs::path& inputFile = entry.path();
        fs::path outputFile = output_path / inputFile.filename();
        outputFile.replace_extension("wav");

        convertMP3ToWAV(inputFile, outputFile);

        cout << inputFile.filename().c_str() << " converted to WAV." << endl;
    }

    return 0;
}

