library ieee;
use ieee.std_logic_1164.all;
entity CA is
   port( adr : in std_logic_vector(3 downto 0) ;
         clk, sel, init : in std_logic;
         Y : out std_logic 
);
end CA;
architecture behavior of CA is
signal X: std_logic;

begin
  with adr select
    X <= '0' when "0000",
         '1' when "0001",
         '1' when "0010",
         '0' when "0011",
         '0' when "0100",
         '0' when "0101",
         '0' when "0110",
         '1' when "0111",
         '1' when "1000",
         '1' when "1001",
         '1' when "1010",
         '0' when "1011",
         '0' when "1100",
         '1' when "1101",
         '0' when "1110",
         '1' when "1111",
         '1' when others;
         process(clk)
     begin
      if (clk'EVENT and clk = '1')  then
		if (sel = '0') then
			Y <= init;
		else
			Y <= X;
		end if;
      end if;
     end process;
end behavior;

---------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
entity RNG is
  port(seed : in std_logic_vector(63 downto 0);
       clk, sel : in std_logic;
       rng_out : out std_logic_vector(63 downto 0)
   );
end RNG;
architecture structure of RNG is
type CA_input is array (63 downto 0) of std_logic_vector(3 downto 0);
component CA 
   port( adr : in std_logic_vector(3 downto 0) ;
         clk, sel, init : in std_logic;
         Y : out std_logic 
);
end component;

signal my_CA_input: CA_input;
signal my_CA_output: std_logic_vector(63 downto 0);
begin

process (my_CA_output)
   variable j,k,l : integer;
   begin
     for i in 63 downto 0 loop
      j := i-1;
      if j<0 then j:= 63; end if;
      k := i+2;
      if k>63 then k:=k-64; end if;
      l := i+1;
      if l>63 then l:=l-64; end if;
      my_CA_input(i)<=my_CA_output(i) & my_CA_output(j) 
                             & my_CA_output(k) & my_CA_output(l);
     end loop ;
   end process ;

CA_generate: for n in 63 downto 0 generate
              CA_Array : CA   port map (adr => my_CA_input(n),
                               clk => clk, sel => sel, init => seed(n),
                                 Y => my_CA_output(n));
             end generate ;

rng_out <= my_CA_output;

end structure;

-----------------------------------------------------------------

library ieee;
use std.textio.all;
use ieee.std_logic_1164.all;
use ieee.std_logic_textio.all;

entity test_bench_3 is
end;
--
architecture arch_test of test_bench_3 is
--
signal clk: std_logic := '0';
signal sel: std_logic;
signal seed : std_logic_vector(63 downto 0);
signal rng_out : std_logic_vector(63 downto 0);
--
component RNG 
  port(seed : in std_logic_vector(63 downto 0);
       clk : in std_logic;
       sel : in std_logic;
       rng_out : out std_logic_vector(63 downto 0)
   );
end component;
--
begin
-- Set a clock with period 100 ns
  clk <= '1' after 50 ns when clk='0' else
         '0' after 50 ns; 
-- Set sel
  sel <= '0', '1' after 100 ns;
--
-- This is the process for reading data from a text file
--
process
  file source_data : text is in "source_data.txt";
  variable in_data : line;
  variable temp : std_logic_vector(63 downto 0); 
--
  begin
     readline(source_data,in_data);
     read(in_data,temp);  
     seed <= temp;
    wait;
end process;
--
-- This is the entity under test
--
TEST_TARGET: RNG port map (seed,clk,sel,rng_out);
--
-- This is the process for writing simulation results to a text file
--
process(rng_out)
file output_data : text is out "output_data.txt";
variable out_data : line;
begin
-- if(rng_out /= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU")then
 if (rng_out /= (rng_out'range => 'U')) then
 write(out_data,rng_out);
 writeline(output_data,out_data);
 end if;
end process;
end arch_test;
