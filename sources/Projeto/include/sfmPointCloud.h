#ifndef SFM_POINT_CLOUD_H
#define SFM_POINT_CLOUD_H

/********** Headers **********/

// libc++
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/sfm.hpp>

// internos
#include <cmdline_parser.h>

/********** sfmPointCloud.h **********/

/**
 * Implementa os algoritmos do módulo cv::sfm.
*/
class sfmPointCloud {
private:
	/********** Membros Privados **********/
	const ctrl::args& 			_args; 			/** Argumentos validados extraídos da linha de comando. */
	std::vector<fs::path> 		_images; 		/** Caminhos absolutos até as imagens do dataset. */
	cv::Mat 					_K; 			/** Matriz intrínseca K estimada. Inicialmente derivada dos argumentos <f>, <cx> e <cy>. */
	std::vector<cv::Affine3d> 	_Rts; 			/** Matrizes extrínsecas Rt estimadas para cada câmera. */
	std::vector<cv::Mat> 		_points3d; 		/** Pontos 3D estimados. */
	std::vector<cv::Vec3f> 		_point_cloud; 	/** Nuvem de pontos esparsa. */

public:
	/********** Construtores & Destrutor **********/

	sfmPointCloud() = delete;
	sfmPointCloud(const sfmPointCloud&) = delete;
	sfmPointCloud(sfmPointCloud&&) = delete;
	sfmPointCloud(const ctrl::args&);

	virtual ~sfmPointCloud();

private:
	/********** Funções Membro Privadas **********/

	void export_cloud_OBJ(const fs::path& output_dir = "./output/") const;
	void export_pose_SFM(const fs::path& output_dir = "./output/") const;

public:
	/********** Funções Membro Públicas **********/
	
	void compute_sparse();
};

#endif // SFM_POINT_CLOUD_H