Projeto Sistemas Operativos: Exercicio 2 - 18/19
90707 Bruno Codinha 
90709 Catarina Gonçalves


i) Estrutas de diretoria: 

	projeto2/

		doTest.sh

		results/


		inputs/

			generate.py
			random-x32-y32-z3-n64.txt
			random-x32-y32-z3-n96.txt
			random-x48-y48-z3-n48.txt
			random-x48-y48-z3-n64.txt
			random-x64-y64-z3-n48.txt
			random-x64-y64-z3-n64.txt
			random-x128-y128-z3-n64.txt
			random-x128-y128-z3-n128.txt
			random-x128-y128-z5-n128.txt
			random-x256-y256-z3-n256.txt
			random-x256-y256-z5-n256.txt
			random-x512-y512-z7-n512.txt

		SimpleShell/

			CircuitRouter-SimpleShell.c

			inputs/
				generate.py
				random-x32-y32-z3-n64.txt
				random-x32-y32-z3-n96.txt
				random-x48-y48-z3-n48.txt
				random-x48-y48-z3-n64.txt
				random-x64-y64-z3-n48.txt
				random-x64-y64-z3-n64.txt
				random-x128-y128-z3-n64.txt
				random-x128-y128-z3-n128.txt
				random-x128-y128-z5-n128.txt
				random-x256-y256-z3-n256.txt
				random-x256-y256-z5-n256.txt
				random-x512-y512-z7-n512.txt


		SeqSolver/

			grid.c
			grid.h
			maze.c
			maze.h
			router.c
			router.h
			Makefile
			coordinate.c
			coordinate.h
			CircuitRouter-SeqSolver.c


		ParSolver/

			grid.c
			grid.h
			maze.c
			maze.h
			router.c
			router.h
			Makefile
			coordinate.c
			coordinate.h
			CircuitRouter-ParSolver.c

			inputs/
				generate.py
				random-x32-y32-z3-n64.txt
				random-x32-y32-z3-n96.txt
				random-x48-y48-z3-n48.txt
				random-x48-y48-z3-n64.txt
				random-x64-y64-z3-n48.txt
				random-x64-y64-z3-n64.txt
				random-x128-y128-z3-n64.txt
				random-x128-y128-z3-n128.txt
				random-x128-y128-z5-n128.txt
				random-x256-y256-z3-n256.txt
				random-x256-y256-z5-n256.txt
				random-x512-y512-z7-n512.txt


		lib/
			
			list.c
			list.h
			pair.c
			pair.h
			queue.c
			queue.h
			timer.h
			types.h
			vecotr.c
			vector.h
			utility.h
			commandlinereader.c
			commandlinereader.h



ii) Passos para compilar:

		1 - aceder a diretoria que se pertende, ou seja, aceder a projeto2/.

				~/...$ cd projeto2/

		2 - utilizar o comando make

	Passo para executar:

		3 - caso se pretenda executar o ParSolver deve-se escrever no terminal:
			./CircuitRouter-ParSolver -t MAXTHREADS inputs/...

		  - caso se pretenda executar o SeqSolver deve-se escrever no terminal:
			./CircuitRouter-SeqSolver inputs/...

		  - caso se pretenda executar o doTest.sh deve-se escrever no terminal:
			./doTest.sh MAXTHREADS inputs/...



iii) Caracteristicas do processador 


	processor	: 0
	vendor_id	: GenuineIntel
	cpu family	: 6
	model		: 142
	model name	: Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz
	stepping	: 9
	microcode	: 0x8e
	cpu MHz		: 1831.043
	cache size	: 4096 KB
	physical id	: 0
	siblings	: 4
	core id		: 0
	cpu cores	: 2
	apicid		: 0
	initial apicid	: 0
	fpu		: yes
	fpu_exception	: yes
	cpuid level	: 22
	wp		: yes
	flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp flush_l1d
	bugs		: cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf
	bogomips	: 5810.00
	clflush size	: 64
	cache_alignment	: 64
	address sizes	: 39 bits physical, 48 bits virtual
	power management:

	processor	: 1
	vendor_id	: GenuineIntel
	cpu family	: 6
	model		: 142
	model name	: Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz
	stepping	: 9
	microcode	: 0x8e
	cpu MHz		: 1819.914
	cache size	: 4096 KB
	physical id	: 0
	siblings	: 4
	core id		: 1
	cpu cores	: 2
	apicid		: 2
	initial apicid	: 2
	fpu		: yes
	fpu_exception	: yes
	cpuid level	: 22
	wp		: yes
	flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp
	bugs		: cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf
	bogomips	: 5810.00
	clflush size	: 64
	cache_alignment	: 64
	address sizes	: 39 bits physical, 48 bits virtual
	power management:

	processor	: 2
	vendor_id	: GenuineIntel
	cpu family	: 6
	model		: 142
	model name	: Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz
	stepping	: 9
	microcode	: 0x8e
	cpu MHz		: 1579.083
	cache size	: 4096 KB
	physical id	: 0
	siblings	: 4
	core id		: 0
	cpu cores	: 2
	apicid		: 1
	initial apicid	: 1
	fpu		: yes
	fpu_exception	: yes
	cpuid level	: 22
	wp		: yes
	flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp flush_l1d
	bugs		: cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf
	bogomips	: 5810.00
	clflush size	: 64
	cache_alignment	: 64
	address sizes	: 39 bits physical, 48 bits virtual
	power management:

	processor	: 3
	vendor_id	: GenuineIntel
	cpu family	: 6
	model		: 142
	model name	: Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz
	stepping	: 9
	microcode	: 0x8e
	cpu MHz		: 1825.424
	cache size	: 4096 KB
	physical id	: 0
	siblings	: 4
	core id		: 1
	cpu cores	: 2
	apicid		: 3
	initial apicid	: 3
	fpu		: yes
	fpu_exception	: yes
	cpuid level	: 22
	wp		: yes
	flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp flush_l1d
	bugs		: cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf
	bogomips	: 5810.00
	clflush size	: 64
	cache_alignment	: 64
	address sizes	: 39 bits physical, 48 bits virtual
	power management:




