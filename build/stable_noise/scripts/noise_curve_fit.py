import os
import numpy
import scipy.optimize
import math
import noise_lookup_tables as nlt
import noise_lookup_tables_3d as nlt3d

def match_1d_noise(noise_name):

    noise_data_dict = {"noise":  (nlt.silib_noise_range_lookup,  (0.10, 2.0, 0.5), False),
                       "xnoise": (nlt.silib_xnoise_range_lookup, (0.05, 2.0, 0.5), False),
                       "onoise": (nlt.silib_onoise_range_lookup, (0.05, 3.0, 0.7), False),
                       "snoise": (nlt.silib_snoise_range_lookup, (0.05, 2.0, 0.5), True ),
                       "anoise": (nlt.silib_anoise_range_lookup, (0.05, 2.0, 0.5), False)}

    noise_func = noise_data_dict[noise_name][0]
    init_guess = noise_data_dict[noise_name][1]
    use_error  = noise_data_dict[noise_name][2]

    resultA=[]
    resultB=[]
    resultC=[]

    print "\n{0}".format(noise_name)

    for j in xrange(10):
        octaves = j+1
        x=[]
        y=[]
        sd=[]
        for i in xrange(11):
            roughness = i*0.1
            amplitude = noise_func(roughness,octaves)
            err = 0.0001 + roughness*0.1;
            x.append(roughness)
            y.append(amplitude)
            sd.append(err)

        if use_error:
            result = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(y), p0=init_guess, sigma = sd)
        else:
            result = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(y), p0=init_guess)

        
        print "({0}, {1}, {2}),".format(*result[0])
        resultA.append(result[0][0])
        resultB.append(result[0][1])
        resultC.append(result[0][2])
        

    # Analyse how the A, B, and C variables vary with octave and generate curves.
    # This smooths out localised dips in the data and stops wobbles of amplitude as we vary across roughness and octaves
    x = [j+1 for j in xrange(10)]

    fitA = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultA))

    try:
        fitB = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultB))
    except:
        print "regressing to linear fit"
        fitB = scipy.optimize.curve_fit(lambda t,a,c: a*numpy.power(t,1)+c,  numpy.array(x),  numpy.array(resultB))
        fitB = ((fitB[0][0], 1, fitB[0][1]), fitB[1])

    fitC = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultC), p0=[0.1,0.1,0.1])

    print "A: ({0}, {1}, {2}),".format(*fitA[0])
    print "B: ({0}, {1}, {2}),".format(*fitB[0])
    print "C: ({0}, {1}, {2}),".format(*fitC[0])

    # Strip off covariance part of results
    return (fitA[0], fitB[0], fitC[0])


def generate_1d_noise_amplitude_lookup_vex(noise_name, fitA, fitB, fitC):

    lookup_A = []
    lookup_B = []
    lookup_C = []

    vex_code="""
float silib_{0}_amplitude_lookup(const float rough; const int _octaves)
{{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A[] = {{ {1} }};
    float lookup_B[] = {{ {2} }};
    float lookup_C[] = {{ {3} }};
    if(octaves <= 0) return lookup_C[0]; // Force to a flat profile (only 1 octave)
    return lookup_A[octaves] * pow(rough, lookup_B[octaves]) + lookup_C[octaves];
}}

"""
    for i in xrange(10):
        octaves = i+1
        lookup_A.append(fitA[0]*math.pow(octaves, fitA[1]) + fitA[2])
        lookup_B.append(fitB[0]*math.pow(octaves, fitB[1]) + fitB[2])
        lookup_C.append(fitC[0]*math.pow(octaves, fitC[1]) + fitC[2])

    return vex_code.format(noise_name, str(lookup_A)[1:-1], str(lookup_B)[1:-1], str(lookup_C)[1:-1])


def match_3d_noise(noise_name):

    noise_data_dict = {"noise":  (nlt3d.silib_noise_range_lookup_3d,  ((0.10, 2.0, 0.5), (0.10, 2.0, 0.5), (0.10, 2.0, 0.5)), False),
                       "xnoise": (nlt3d.silib_xnoise_range_lookup_3d, ((0.05, 2.0, 0.5), (0.05, 2.0, 0.5), (0.05, 2.0, 0.5)), False),
                       "onoise": (nlt3d.silib_onoise_range_lookup_3d, ((0.05, 3.0, 0.7), (0.05, 3.0, 0.7), (0.05, 3.0, 0.7)), False),
                       "snoise": (nlt3d.silib_snoise_range_lookup_3d, ((0.05, 2.0, 0.5), (0.05, 2.0, 0.5), (0.05, 2.0, 0.5)), True ),
                       "anoise": (nlt3d.silib_anoise_range_lookup_3d, ((0.05, 2.0, 0.5), (0.05, 2.0, 0.5), (0.05, 2.0, 0.5)), False)}

    noise_func = noise_data_dict[noise_name][0]
    init_guess = noise_data_dict[noise_name][1]
    use_error  = noise_data_dict[noise_name][2]

    resultA = [[],[],[]]
    resultB = [[],[],[]]
    resultC = [[],[],[]]

    print "\n{0} 3d".format(noise_name)

    for j in xrange(10):
        octaves = j+1
        x=[]
        y=[[],[],[]]
        sd=[]
        for i in xrange(11):
            roughness = i*0.1
            amplitude_3d = noise_func(roughness,octaves)
            err = 0.0001 + roughness*0.1;
            x.append(roughness)
            y[0].append(amplitude_3d[0])
            y[1].append(amplitude_3d[1])
            y[2].append(amplitude_3d[2])
            sd.append(err)

        result = [None, None, None]
        for i in xrange(3):
            if use_error:
                result[i] = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(y[i]), p0=init_guess[i], sigma = sd)
            else:
                result[i] = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(y[i]), p0=init_guess[i])
            
            print "({0}, {1}, {2}),".format(*result[i][0])
            resultA[i].append(result[i][0][0])
            resultB[i].append(result[i][0][1])
            resultC[i].append(result[i][0][2])
        
    x = [j+1 for j in xrange(10)]

    fitA = [[],[],[]]
    fitB = [[],[],[]]
    fitC = [[],[],[]]
    for i in xrange(3):
        # Analyse how the A, B, and C variables vary with octave and generate curves.
        # This smooths out localised dips in the data and stops wobbles of amplitude as we vary across roughness and octaves
        fitA[i] = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultA[i]))

        try:
            fitB[i] = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultB[i]))
        except:
            print "regressing to linear fit"
            fitB[i] = scipy.optimize.curve_fit(lambda t,a,c: a*numpy.power(t,1)+c,  numpy.array(x),  numpy.array(resultB[i]))
            fitB[i] = ((fitB[i][0][0], 1, fitB[i][0][1]), fitB[i][1])

        try:
            fitC[i] = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultC[i]), p0=[0.1,0.1,0.1])
        except:
            fitC[i] = scipy.optimize.curve_fit(lambda t,a,b,c: a*numpy.power(t,b)+c,  numpy.array(x),  numpy.array(resultC[i]), p0=[0.1,1.0,1.0])

        print "A: ({0}, {1}, {2}),".format(*fitA[i][0])
        print "B: ({0}, {1}, {2}),".format(*fitB[i][0])
        print "C: ({0}, {1}, {2}),".format(*fitC[i][0])

    # Strip off covariance part of results
    for i in xrange(3):
        fitA[i] = fitA[i][0]
        fitB[i] = fitB[i][0]
        fitC[i] = fitC[i][0]

    return (fitA, fitB, fitC)


def generate_3d_noise_amplitude_lookup_vex(noise_name, fitA, fitB, fitC):

    lookup_A = [[],[],[]]
    lookup_B = [[],[],[]]
    lookup_C = [[],[],[]]


    vex_code="""
vector silib_{0}_amplitude_lookup_3d(const float rough; const int _octaves)
{{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A0[] = {{ {1} }};
    float lookup_B0[] = {{ {2} }};
    float lookup_C0[] = {{ {3} }};
    float lookup_A1[] = {{ {4} }};
    float lookup_B1[] = {{ {5} }};
    float lookup_C1[] = {{ {6} }};
    float lookup_A2[] = {{ {7} }};
    float lookup_B2[] = {{ {8} }};
    float lookup_C2[] = {{ {9} }};
    if(octaves <= 0) return set(lookup_C0[0], lookup_C1[0], lookup_C2[0]); // Force to a flat profile (only 1 octave)
    return set(lookup_A0[octaves] * pow(rough, lookup_B0[octaves]) + lookup_C0[octaves], 
               lookup_A1[octaves] * pow(rough, lookup_B1[octaves]) + lookup_C1[octaves],
               lookup_A2[octaves] * pow(rough, lookup_B2[octaves]) + lookup_C2[octaves]);
}}

"""
    for j in xrange(3):
        for i in xrange(10):
            octaves = i+1
            lookup_A[j].append(fitA[j][0]*math.pow(octaves, fitA[j][1]) + fitA[j][2])
            lookup_B[j].append(fitB[j][0]*math.pow(octaves, fitB[j][1]) + fitB[j][2])
            lookup_C[j].append(fitC[j][0]*math.pow(octaves, fitC[j][1]) + fitC[j][2])

    return vex_code.format(noise_name, str(lookup_A[0])[1:-1], str(lookup_B[0])[1:-1], str(lookup_C[0])[1:-1],
                           str(lookup_A[1])[1:-1], str(lookup_B[1])[1:-1], str(lookup_C[1])[1:-1],
                           str(lookup_A[2])[1:-1], str(lookup_B[2])[1:-1], str(lookup_C[2])[1:-1])



def generate_code(out_type, out_char, in_type, in_char, noise_fn, lookup_fn, remap_in_fn, remap_out_fn):
    code = """
{out_type} si_{noise_fn}{out_char}{in_char}({in_type} pos; {in_type} freq; {in_type} offset; float rough; int octaves)
{{  
    {in_type} pp = pos * freq - offset;
    
    {out_type} nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {{
        nval += local_amp * ({remap_in_fn});
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }}

    {out_type} amp_out = {lookup_fn}(rough, octaves);
    nval = {remap_out_fn};    
    
    return nval;
}}
"""

    remap_in_fn = remap_in_fn.format(noise_fn=noise_fn, out_type=out_type, in_type=in_type)
    remap_out_fn = remap_out_fn.format(noise_fn=noise_fn, out_type=out_type, in_type=in_type)
    lookup_fn = lookup_fn.format(noise_fn=noise_fn);
    
    return code.format(out_type=out_type, out_char=out_char, in_type=in_type, in_char=in_char, noise_fn=noise_fn, lookup_fn=lookup_fn, remap_in_fn=remap_in_fn, remap_out_fn=remap_out_fn)

    
def generate_noise_functions():
   
    output_str=""
    
    in_remap_m1_1 = "2*({out_type}({noise_fn}(pp))-0.5)"
    in_remap_none = "{out_type}({noise_fn}(pp))"
    
    out_remap_m1_1 = "nval/amp_out"
    out_remap_none = "nval"
    
    noisefn_list = (("noise", in_remap_m1_1, out_remap_m1_1, True),
                    ("xnoise", in_remap_m1_1, out_remap_m1_1, True),
                    ("onoise", in_remap_none, out_remap_m1_1, False),
                    ("snoise", in_remap_none, out_remap_m1_1, False),
                    ("anoise", in_remap_none, out_remap_m1_1, False))
    
    for item in noisefn_list:
        noise_fn = item[0]
        remap_in_fn = item[1]
        remap_out_fn = item[2]
        supports_extended_types = item[3]
                    
        output_str += generate_code("float", "f", "vector", "v", noise_fn, "silib_{noise_fn}_amplitude_lookup", remap_in_fn, remap_out_fn)
        output_str += generate_code("vector", "v", "vector", "v", noise_fn, "silib_{noise_fn}_amplitude_lookup_3d", remap_in_fn, remap_out_fn)        
        
        if supports_extended_types:
            output_str += generate_code("float", "f", "float", "f", noise_fn, "silib_{noise_fn}_amplitude_lookup", remap_in_fn, remap_out_fn)
            output_str += generate_code("float", "f", "vector4", "p", noise_fn, "silib_{noise_fn}_amplitude_lookup", remap_in_fn, remap_out_fn)
            output_str += generate_code("vector", "v", "float", "f", noise_fn, "silib_{noise_fn}_amplitude_lookup_3d", remap_in_fn, remap_out_fn)
            output_str += generate_code("vector", "v", "vector4", "p", noise_fn, "silib_{noise_fn}_amplitude_lookup_3d", remap_in_fn, remap_out_fn)


    return output_str


def main():

    final_vex_code = ""
    noise_name_list = ["noise", "xnoise", "onoise", "snoise", "anoise"]

    for noise_name in noise_name_list:
        fitA, fitB, fitC = match_1d_noise(noise_name)
        final_vex_code += generate_1d_noise_amplitude_lookup_vex(noise_name, fitA, fitB, fitC)

    for noise_name in noise_name_list:
        fitA, fitB, fitC = match_3d_noise(noise_name)
        final_vex_code += generate_3d_noise_amplitude_lookup_vex(noise_name, fitA, fitB, fitC)

    final_vex_code += generate_noise_functions()

    fname = os.path.normpath(os.path.join(os.path.dirname(__file__),"..","vex","si_noise.h"))
    with open(fname,"w") as fhandle:
        fhandle.write(final_vex_code)

main()
