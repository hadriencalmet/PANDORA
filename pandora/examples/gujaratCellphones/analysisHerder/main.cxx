/*
 * Copyright (c) 2012
 * COMPUTER APPLICATIONS IN SCIENCE & ENGINEERING
 * BARCELONA SUPERCOMPUTING CENTRE - CENTRO NACIONAL DE SUPERCOMPUTACIÓN
 * http://www.bsc.es

 * This file is part of Pandora Library. This library is free software; 
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 3.0 of the License, or (at your option) any later version.
 * 
 * Pandora is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <Exceptions.hxx>
#include <SimulationRecord.hxx>

#include <analysis/Results.hxx>
#include <analysis/AgentMean.hxx>
#include <analysis/AgentStdDev.hxx>
#include <analysis/AgentSum.hxx>
#include <analysis/AgentNum.hxx>
#include <iostream>

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		throw Engine::Exception("USAGE: analysis file.h5 agent.csv");
		return 0;
	}

	try
	{
		Engine::SimulationRecord simRecord( 1, false);
		simRecord.loadHDF5(argv[1], false, true);

		Analysis::AgentResults agentResults(simRecord, argv[2], "Herder");
		agentResults.addAnalysis(new Analysis::AgentNum());
		agentResults.addAnalysis(new Analysis::AgentMean("starvation x100"));
		agentResults.addAnalysis(new Analysis::AgentMean("herd size"));
//		agentResults.addAnalysis(new Analysis::AgentStdDev("herd size"));
		//agentResults.addAnalysis(new Analysis::AgentMean("needed resources"));

		agentResults.apply();
	}
	catch( std::exception & exceptionThrown )
	{
		std::cout << "exception thrown: " << exceptionThrown.what() << std::endl;
		return -1;
	}
	return 0;
}
