--------------------------------------------------------------------------------
-- Procesador MIPS con pipeline curso Arquitectura 2018-19
--
-- Autores:
--		Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
--		David Cabornero Pascual - david.cabornero@estudiante.uam.es
-- Grupo: 1311
-- Pareja: PM19
-- Fecha: 06/10/2018
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity processor is
   port(
      Clk         : in  std_logic; -- Reloj activo flanco subida
      Reset       : in  std_logic; -- Reset asincrono activo nivel alto
      -- Instruction memory
      IAddr      : out std_logic_vector(31 downto 0); -- Direccion
      IDataIn    : in  std_logic_vector(31 downto 0); -- Dato leido
      -- Data memory
      DAddr      : out std_logic_vector(31 downto 0); -- Direccion
      DRdEn      : out std_logic;                     -- Habilitacion lectura
      DWrEn      : out std_logic;                     -- Habilitacion escritura
      DDataOut   : out std_logic_vector(31 downto 0); -- Dato escrito
      DDataIn    : in  std_logic_vector(31 downto 0)  -- Dato leido
   );
end processor;

architecture rtl of processor is 
	
	-- ************* COMPONENTS ************* --
	component control_unit
		port(
		-- Entrada = codigo de operacion en la instruccion:
		OpCode  : in  std_logic_vector (5 downto 0);
		-- Seniales para el PC
		Branch : out  std_logic; -- 1=Ejecutandose instruccion branch
		Jump : out std_logic; -- 1=Ejecutandose instruccion jump
		-- Seniales relativas a la memoria
		MemToReg : out  std_logic; -- 1=Escribir en registro la salida de la mem.
		MemWrite : out  std_logic; -- Escribir la memoria
		MemRead  : out  std_logic; -- Leer la memoria
		-- Seniales para la ALU
		ALUSrc : out  std_logic;                     -- 0=oper.B es registro, 1=es valor inm.
		ALUOp  : out  std_logic_vector (2 downto 0); -- Tipo operacion para control de la ALU
		-- Seniales para el GPR
		RegWrite : out  std_logic; -- 1=Escribir registro
		RegDst   : out  std_logic  -- 0=Reg. destino es rt, 1=rd
		);
	end component;
	
	component reg_bank
		port(
		Clk   : in std_logic; -- Reloj activo en flanco de subida
		Reset : in std_logic; -- Reset asíncrono a nivel alto
		A1    : in std_logic_vector(4 downto 0);   -- Dirección para el puerto Rd1
		Rd1   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd1
		A2    : in std_logic_vector(4 downto 0);   -- Dirección para el puerto Rd2
		Rd2   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd2
		A3    : in std_logic_vector(4 downto 0);   -- Dirección para el puerto Wd3
		Wd3   : in std_logic_vector(31 downto 0);  -- Dato de entrada Wd3
		We3   : in std_logic -- Habilitación de la escritura de Wd3
		);
	end component;
	
	component alu_control
		port(
		-- Entradas:
		ALUOp  : in std_logic_vector (2 downto 0); -- Codigo control desde la unidad de control
		Funct  : in std_logic_vector (5 downto 0); -- Campo "funct" de la instruccion
		-- Salida de control para la ALU:
		ALUControl : out std_logic_vector (3 downto 0) -- Define operacion a ejecutar por ALU
		);
	end component;
	
	component alu
		port (
		OpA     : in  std_logic_vector (31 downto 0); -- Operando A
		OpB     : in  std_logic_vector (31 downto 0); -- Operando B
		Control : in  std_logic_vector ( 3 downto 0); -- Codigo de control=op. a ejecutar
		Result  : out std_logic_vector (31 downto 0); -- Resultado
		ZFlag   : out std_logic                       -- Flag Z
		);
	end component;
	-- **************************************************************************************** --
	
	signal OpCode  : std_logic_vector(5 downto 0);
	signal Branch : std_logic;
	signal Jump : std_logic; 
	signal MemToReg : std_logic;
	signal MemWrite : std_logic;
	signal MemRead  : std_logic;
	signal ALUSrc : std_logic;
	signal ALUOp  : std_logic_vector(2 downto 0);
	signal RegWrite : std_logic;
	signal RegDst   : std_logic;
	
	signal Rd1   : std_logic_vector(31 downto 0);
	signal Rd2   : std_logic_vector(31 downto 0);
	
	signal ZFlag : std_logic;
	
	signal Funct  : std_logic_vector (5 downto 0);
	signal ALUControl : std_logic_vector (3 downto 0);
	
	signal DAddrAux : std_logic_vector(31 downto 0);
	signal IAddrAux : std_logic_vector(31 downto 0);
	
	signal MuxMemToReg : std_logic_vector(31 downto 0);
	signal MuxRegDst : std_logic_vector(4 downto 0);
	signal MuxALUSrc : std_logic_vector(31 downto 0);
	signal MuxJump : std_logic_vector(31 downto 0);
	signal MuxPCSrc : std_logic_vector(31 downto 0);
	
	signal PCPlus4 : std_logic_vector(31 downto 0);
	signal PCSrc : std_logic;
	signal SignExt : std_logic_vector(31 downto 0);
	signal SignExt4 : std_logic_vector(31 downto 0);
	signal AuxiliaryALU : std_logic_vector(31 downto 0);
	signal JumpAddr : std_logic_vector(31 downto 0);
	
begin   
	
	reg_back_inst: reg_bank port map(
		Clk => Clk,
		Reset => Reset,
		We3 => RegWrite,
		Wd3 => MuxMemToReg,
		A1 => IDataIn(25 downto 21),
		A2 => IDataIn(20 downto 16),
		A3 => MuxRegDst,
		Rd1 => Rd1,
		Rd2 => Rd2
		);
	
	alu_inst: alu port map(
		OpA => Rd1,
		OpB => MuxALUSrc,
		Control => ALUControl,
		Result => DAddrAux,
		ZFlag => ZFlag
		);
	
	control_unit_inst: control_unit port map(
		OpCode => IDataIn(31 downto 26),
		Branch => Branch,
		Jump => Jump,
		MemToReg => MemToReg,
		MemWrite => MemWrite,
		MemRead => MemRead,
		ALUSrc => ALUSrc, 
		ALUOp => ALUOp,
		RegWrite => RegWrite,
		RegDst => RegDst
		);
	
	alu_control_inst: alu_control port map(
		ALUOp => ALUOp,
		Funct => IDataIn(5 downto 0),
		ALUControl => ALUControl
	);
	
	process(Clk, Reset)
	begin
		if(Reset = '1') then
			IAddrAux <= (others => '0');
		elsif rising_edge(Clk) then
			IAddrAux <= MuxJump;
		end if;
	end process;
	
	--Salidas que tienen que leerse
	IAddr <= IAddrAux;
	DAddr <= DAddrAux;
	
	--Señales intermedias
	PCPlus4 <= IAddrAux + 4;
	DDataOut <= Rd2;
	DWrEn <= MemWrite;
	DRdEn <= MemRead;
	PCSrc <= Branch and ZFlag;
	
	SignExt(15 downto 0) <= IDataIn(15 downto 0);
	SignExt(31 downto 16) <= (others => IDataIn(15));
	SignExt4(31 downto 2) <= SignExt(29 downto 0);
	SignExt4(1 downto 0) <= (others => '0');
	
	AuxiliaryALU <= SignExt4 + PCPlus4;
	
	JumpAddr(31 downto 28) <= PCPlus4(31 downto 28);
	JumpAddr(27 downto 2) <= IDataIn(25 downto 0);
	JumpAddr(1 downto 0) <= (others => '0');
	
	--Multiplexores
	MuxPCSrc <= AuxiliaryALU when PCSrc='1' else PCPlus4;
	MuxJump <= JumpAddr when Jump='1' else MuxPCSrc;
	MuxRegDst <= IDataIn(15 downto 11) when RegDst='1' else IDataIn(20 downto 16);
	MuxALUSrc <= Rd2 when ALUSrc='0' else SignExt;
	MuxMemToReg <= DAddrAux when MemToReg='0' else DDataIn;
		
	
	
end architecture;
