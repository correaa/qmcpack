
#ifndef ADIOS_ADIOS_CONFIG_H
#define ADIOS_ADIOS_CONFIG_H

#include <string>
#include <Configuration.h>

namespace ADIOS
{
void initialize(bool use_hdf5, bool use_adios);
void initialze(std::string &xml_filename, bool use_hdf5, bool use_adios);
bool useADIOS();
bool useHDF5();
const std::string& get_adios_xml();
};

#endif
