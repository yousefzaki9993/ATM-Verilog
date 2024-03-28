vlib work
vlog ATM_Banking_System.v ATM_Banking_System_tb.v +cover -covercells
vsim -voptargs=+acc work.ATM_TB -cover
add wave *
coverage save ATM_Banking_System.ucdb -onexit 
run -all