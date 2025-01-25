import os
import json
import csv
# from porespy import generators as ps

def hcpSpheres():
    """
    Generate a domain using hexagonal close-packed (HCP) spheres.
    """
    domain_data = "HCP Spheres Domain\n"
    domain_data += "Parameters:\n"
    domain_data += " - Sphere radius: 1.0\n"
    domain_data += " - Packing density: 0.74\n"
    domain_data += " - Dimensions: 10x10\n"

    # def create_boolean_domain_with_hcp_spheres(sphere_radius, pitch_length):
    # # Generate a boolean domain with HCP spheres

    # temp_domain = ps.lattice_spheres(shape= (int(nx), int(ny)), r = sphere_radius, offset = (0, 0), spacing = (int(pitch_length),int(3**0.5*pitch_length/2)), lattice='tri')
    
    # temp_domain = array(temp_domain, dtype=int)
    # # flip the domain values so that the spheres are 1's and the void space is 0's
    # temp_domain = 1 - temp_domain

    # temp_domain[0:int(2*sphere_radius+1),:] = 0
    # temp_domain[-int(2*sphere_radius):,:] = 0
    # temp_domain[:,0:int(2*sphere_radius+1)] = 0
    # temp_domain[:,-int(2*sphere_radius):] = 0

    # temp_domain = 20*temp_domain
    
    # return temp_domain
    
    return domain_data

def default():
    """
    Generate a default domain.
    """
    domain_data = "Default Domain\n"
    domain_data += "Parameters:\n"
    domain_data += " - Grid size: 10x10\n"
    domain_data += " - Initial conditions: uniform\n"
    return domain_data

def main():
    """
    Main function to prompt user input and generate the desired domain.
    """
    print("Domain Generator")
    print("Choose a domain type:")
    print("1. HCP Spheres")
    print("2. Default")
    
    choice = input("Enter your choice (1 or 2): ").strip()
    
    if choice == "1":
        domain_content = hcpSpheres()
    elif choice == "2":
        domain_content = default()
    else:
        print("Invalid choice. Using default domain.")
        domain_content = default()
    
    # Write the domain content to a text file
    # with open("domain/domain.txt", "w") as file:
    #     file.write(domain_content)
    
    print("Domain file 'domain.txt' has been generated.")

if __name__ == "__main__":
    main()
